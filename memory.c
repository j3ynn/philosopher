/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbellucc <jbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:00:13 by jbellucc          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:14 by jbellucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

void	alloc_memory(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philo)
		return ;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
		return ;
}

void	free_memory(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philo[i].lock);
		i++;
	}
	pthread_mutex_destroy(&data->lock);
	pthread_mutex_destroy(&data->print);
	free(data->philo);
	free(data->forks);
}
