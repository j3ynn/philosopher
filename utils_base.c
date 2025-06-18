
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
	if(data->finish == 1)
		return ;
	printf("%lu %d %s\n", (convert_time() - data->start_time), id, str);
}

int	ft_isdigit(int i)
{
	if (i >= 48 && i <= 57)
		return (1);
	else
		return (0);
}

void	alloc_memory(t_data *data)
{
	data->philo = malloc(sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
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
