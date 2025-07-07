/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbellucc <jbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:55:54 by jbellucc          #+#    #+#             */
/*   Updated: 2025/07/07 15:04:21 by jbellucc         ###   ########.fr       */
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

static int	continue_timer_to_die(t_philo *philo)
{
	uint64_t	meal;
	uint64_t	last_meal_time;
	int			is_eating;

	pthread_mutex_lock(&philo->lock);
	last_meal_time = philo->last_meal;
	is_eating = philo->is_eating;
	pthread_mutex_unlock(&philo->lock);
	meal = convert_time() - last_meal_time;
	if (!is_eating && meal >= (uint64_t)philo->data->time_die)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finish == 0)
		{
			print_status(philo->data, "died", philo->id);
			philo->data->finish = 1;
		}
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	return (0);
}

void	*timer_to_die(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finish == 1)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break ;
		}
		pthread_mutex_unlock(&philo->data->lock);
		if (continue_timer_to_die(philo))
			break ;
		usleep(1000);
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
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finish == 0)
		{
			print_status(philo->data, "died", philo->id);
			philo->data->finish = 1;
		}
		pthread_mutex_unlock(&philo->data->lock);
		return (0);
	}
	return (1);
}
