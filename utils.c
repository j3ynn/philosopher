/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbellucc <jbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:55:54 by jbellucc          #+#    #+#             */
/*   Updated: 2025/07/25 11:48:22 by jbellucc         ###   ########.fr       */
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

int	one_fork(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		custom_usleep(philo->data->time_die);
		pthread_mutex_unlock(philo->fork_s);
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finish == 0)
		{
			printf("%lu %d %s\n", (convert_time() - philo->data->start_time),
				philo->id, "died");
			philo->data->finish = 1;
		}
		pthread_mutex_unlock(&philo->data->lock);
		return (0);
	}
	return (1);
}

int	custom_usleep(uint64_t time)
{
	uint64_t	start;

	start = convert_time();
	while ((convert_time() - start) < time)
		usleep(time / 10);
	return (0);
}
