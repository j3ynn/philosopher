/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbellucc <jbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:50:43 by jbellucc          #+#    #+#             */
/*   Updated: 2025/07/17 17:17:58 by jbellucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_all_full(t_data *data, int i)
{
	if (i >= data->num_philos)
	{
		pthread_mutex_lock(&data->lock);
		data->finish = 1;
		pthread_mutex_lock(&data->print);
		printf("all full\n");
		pthread_mutex_unlock(&data->print);
		pthread_mutex_unlock(&data->lock);
		return (1);
	}
	return (0);
}

void	*monitor_meals(void *arg)
{
	t_data	*data;
	int		i;
	int		status;

	data = (t_data *)arg;
	while (1)
	{
		pthread_mutex_lock(&data->lock);
		status = (data->finish == 0 && data->num_eat > 0);
		pthread_mutex_unlock(&data->lock);
		if (!status)
			break ;
		i = 0;
		while (i < data->num_philos)
		{
			if (!data->philo[i].is_full)
				break ;
			i++;
		}
		if (check_all_full(data, i))
			return (NULL);
	}
	return (NULL);
}

static int	continue_timer_to_die_two(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->lock);
	if (philo->data->finish == 0)
	{
		printf("%lu %d %s\n", (convert_time() - philo->data->start_time),
			philo->id, "died");
		philo->data->finish = 1;
	}
	pthread_mutex_unlock(&philo->data->lock);
	return (1);
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
	if (meal >= (uint64_t)philo->data->time_die)
	{
		pthread_mutex_lock(&philo->lock);
		if (is_eating)
		{
			return (0);
			pthread_mutex_unlock(&philo->lock);
		}
		pthread_mutex_unlock(&philo->lock);
		return (continue_timer_to_die_two(philo));
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
