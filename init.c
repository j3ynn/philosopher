/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbellucc <jbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:09:07 by jbellucc          #+#    #+#             */
/*   Updated: 2025/06/23 15:11:09 by jbellucc         ###   ########.fr       */
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
		data->philo[i].time_die = data->philo[0].time_die;
		data->philo[i].time_to_die = data->start_time + data->philo[i].time_die;
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
	int	i;

	pthread_mutex_init(&data->lock, NULL);
	pthread_mutex_init(&data->print, NULL);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_create(&data->philo[i].thread, NULL, &philo_routine, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}