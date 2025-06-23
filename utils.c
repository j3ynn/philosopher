/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbellucc <jbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:00:26 by jbellucc          #+#    #+#             */
/*   Updated: 2025/06/23 11:00:27 by jbellucc         ###   ########.fr       */
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

void	print_status(t_data *data, char *str, int id)
{
	pthread_mutex_lock(&data->print);
	if (data->finish == 1)
		return ;
	printf("%lu %d %s\n", (convert_time() - data->start_time), id, str);
	pthread_mutex_unlock(&data->print);
}

void	timer_to_die(void *p)
{
	t_philo	*philo;

	philo = (t_philo *)p;
	while (philo->data->finish == 0)
	{
		if ((convert_time() - philo->time_to_die) >= (uint64_t)philo->time_die)
		{
			pthread_mutex_lock(&philo->data->lock);
			pthread_mutex_lock(&philo->data->print);
			print_status(philo->data, "is dead", philo->id);
			philo->data->finish = 1;
			pthread_mutex_unlock(&philo->data->print);
			pthread_mutex_unlock(&philo->data->lock);
			return ;
		}
		usleep(1000);
	}
	return ;
}

int	custom_usleep(uint16_t time)
{
	uint16_t	start;

	start = convert_time();
	while ((convert_time() - start) < time)
		usleep(time / 10);
	return (0);
}

int	one_fork(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->fork_s);
		print_status(philo->data, "has taken a fork", philo->id);
		custom_usleep(philo->time_die);
		pthread_mutex_lock(&philo->data->lock);
		philo->data->finish = 1;
		pthread_mutex_unlock(&philo->data->lock);
		pthread_mutex_unlock(philo->fork_s);
		return (1);
	}
	return (0);
}

