/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbellucc <jbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:51:29 by jbellucc          #+#    #+#             */
/*   Updated: 2025/07/17 16:57:06 by jbellucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].num_eaten = 0;
		data->philo[i].is_eating = 0;
		data->philo[i].dead = false;
		data->philo[i].is_full = false;
		data->philo[i].last_meal = convert_time();
		pthread_mutex_init(&data->philo[i].lock, NULL);
		i++;
	}
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		data->philo[i].fork_s = &data->forks[i];
		if (i == data->num_philos - 1)
		{
			data->philo[i].fork_s = &data->forks[0];
			data->philo[i].fork_d = &data->forks[i];
		}
		else
			data->philo[i].fork_d = &data->forks[i + 1];
		i++;
	}
}

void	init_threads(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	pthread_create(&monitor, NULL, &monitor_meals, data);
	while (i < data->num_philos)
	{
		pthread_create(&data->philo[i].thread, NULL,
			&philo_routine, &data->philo[i]);
		i++;
	}
	i = 0;
	pthread_join(monitor, NULL);
	while (i < data->num_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

void	init(t_data *data, int ac, char **av)
{
	data->num_philos = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	data->start_time = convert_time();
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->lock, NULL);
	data->finish = 0;
	if (ac == 6)
		data->num_eat = ft_atoi(av[5]);
	else
		data->num_eat = 0;
}
