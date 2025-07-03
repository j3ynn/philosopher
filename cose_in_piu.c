#include "philo.h"

void	*monitor_death(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (data->finish == 0 && data->num_eat > 0)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (!data->philo[i].is_full)
				break ;
			i++;
		}
		if (i >= data->num_philos)
		{
			pthread_mutex_lock(&data->lock);
			data->finish = 1;
			printf("all full\n");
			pthread_mutex_unlock(&data->lock);
			return (NULL);
		}
	}
	return (NULL);
}
