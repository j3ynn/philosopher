/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: je <je@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:00:26 by jbellucc          #+#    #+#             */
/*   Updated: 2025/07/03 16:50:48 by je               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

uint64_t	convert_time(void)
{
	struct timeval	tv;
	uint64_t		seconds;
	uint64_t		microseconds;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	seconds = tv.tv_sec * 1000;
	microseconds = tv.tv_usec / 1000;
	return (seconds + microseconds);
}

void	*timer_to_die(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (philo->data->finish == 0)
	{
		if (convert_time() >= (uint64_t)philo->last_meal && !philo->is_eating)
		{
			pthread_mutex_lock(&philo->data->lock);
			print_status(philo->data, "is died", philo->id);
			philo->data->finish = 1;
			pthread_mutex_unlock(&philo->data->lock);
			return (NULL);
		}
	}
	return (NULL);
}

int	custom_usleep(uint64_t time)
{
	uint64_t	start;

	start = convert_time();
	while ((convert_time() - start) < time)
		usleep(time / 10);
	return (0);
}

int	one_fork(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		custom_usleep(philo->data->time_die);
		pthread_mutex_unlock(philo->fork_d);
		print_status(philo->data, "is died", philo->id);
		pthread_mutex_lock(&philo->data->lock);
		philo->data->finish = 1;
		pthread_mutex_unlock(&philo->data->lock);
		return (0);
	}
	return (1);
}

int	check_dead(t_data *data, int i)
{
	if (data->philo[i].dead == true)
	{
		pthread_mutex_lock(&data->lock);
		data->finish = 1;
		pthread_mutex_unlock(&data->lock);
		print_status(data, "is died", data->philo[i].id);
		return (1);
	}
	else
	{
		return (0);
	}
}
