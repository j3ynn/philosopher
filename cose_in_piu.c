#include "philo.h"

void	*monitor_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			pthread_mutex_lock(&data->philo[i].lock);
			if ((convert_time() - data->philo[i].last_meal ) >= data->time_die && !data->philo[i].is_eating)
			{
				pthread_mutex_unlock(&data->philo[i].lock);
				pthread_mutex_lock(&data->lock);
				print_status(data, "died", data->philo[i].id);
				data->finish = 1;
				pthread_mutex_unlock(&data->lock);
				return (NULL);
			}
			pthread_mutex_unlock(&data->philo[i].lock);
			i++;
		}
		pthread_mutex_lock(&data->lock);
		if (data->finish == 1)
		{
			pthread_mutex_unlock(&data->lock);
			break;
		}
		pthread_mutex_unlock(&data->lock);
		usleep(1000);
	}
	return (NULL);
}
