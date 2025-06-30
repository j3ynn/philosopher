/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbellucc <jbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:00:07 by jbellucc          #+#    #+#             */
/*   Updated: 2025/06/30 15:57:58 by jbellucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->fork_d);
	print_status(philo->data, "has taken a destra fork", philo->id);
	if (one_fork(philo) == 0)		
		return ;
	pthread_mutex_lock(philo->fork_s);
	print_status(philo->data, "has taken a sinistra fork", philo->id);
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = 1;
	philo->num_eaten++;
	philo->last_meal = convert_time(); //+ philo->time_die;
	pthread_mutex_unlock(&philo->lock);
	print_status(philo->data, "is eating", philo->id);
	custom_usleep(philo->data->time_eat);
	pthread_mutex_lock(&philo->lock);
	philo->is_eating = 0;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->fork_d);
	pthread_mutex_unlock(philo->fork_s);
}

int	philo_sleep(t_philo *philo)
{
	print_status(philo->data, "is sleeping", philo->id);
	custom_usleep(philo->data->time_sleep);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		custom_usleep(philo->data->time_eat / 2);
	while (1)
	{
		pthread_mutex_lock(&philo->data->lock);
		if (philo->data->finish == 1)
		{
			pthread_mutex_unlock(&philo->data->lock);
			break;
		}
		pthread_mutex_unlock(&philo->data->lock);
		philo_eat(philo);
		if (philo->data->num_eat > 0)
		{
			pthread_mutex_lock(&philo->lock);
			if (philo->num_eaten >= philo->data->num_eat)
			{
				pthread_mutex_unlock(&philo->lock);
				break;
			}
			pthread_mutex_unlock(&philo->lock);
		}
		philo_sleep(philo);
		print_status(philo->data, "is thinking", philo->id);
	}
	return (NULL);
}

void	philo_sated(t_philo *philo)
{
	if (philo->num_eaten >= philo->data->num_eat && philo->data->num_eat > 0)
	{
		pthread_mutex_lock(&philo->data->lock);
		philo->data->finish = 1;
		pthread_mutex_unlock(&philo->lock);
	}
}
