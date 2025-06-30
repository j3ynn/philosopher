/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: je <je@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:09:07 by jbellucc          #+#    #+#             */
/*   Updated: 2025/06/29 14:28:23 by je               ###   ########.fr       */
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
		data->philo[i].eating = 0;
		data->philo[i].dead = false;
		data->philo[i].time_die = data->time_die;
		data->philo[i].time_eat = data->time_eat;
		data->philo[i].time_sleep = data->time_sleep;
		data->philo[i].time_to_die = data->start_time + data->time_die;
		pthread_mutex_init(&data->philo[i].lock, NULL);
		i++;
	}
}

void	init_forks(t_data *data)
{
	int i;

	i = 0;
	if (data->num_philos == 1)
	{
		data->philo[0].fork_s = &data->forks[0];
		data->philo[0].fork_d = NULL;
		return;
	}
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
			data->philo[i].fork_d = &data->forks[0];
		else
			data->philo[i].fork_d = &data->forks[i + 1];
		i++;
	}
}

void	init_threads(t_data *data)
{
	int			i;
	pthread_t	monitor;

	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->print, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, &philo_routine, &data->philo[i]);
		i++;
	}
	pthread_create(&monitor, NULL, &monitor_death, data);
	i = 0;
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
