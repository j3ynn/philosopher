#include "philo.h"

void	philo_eat(t_philo *philo) //da aggiungere Alternanza dell’ordine di presa delle forchette per filosofi pari e dispari
{
	if (one_fork(philo))
		return ;
	pthread_mutex_lock(philo->fork_s);
	print_status(philo->data, "has taken a fork", philo->id);
	pthread_mutex_lock(philo->fork_d);
	print_status(philo->data, "has taken a fork", philo->id);
	pthread_mutex_lock(&philo->lock);
	philo->time_to_die = convert_time() + philo->time_die;
	pthread_mutex_unlock(&philo->lock);
	print_status(philo->data, "is eating", philo->id);
	custom_usleep(philo->time_eat);
	pthread_mutex_lock(&philo->lock);
	philo->num_eaten++;
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_unlock(philo->fork_d);
	pthread_mutex_unlock(philo->fork_s);
}

int	philo_sleep(t_philo *philo)
{
	print_status(philo->data, "is sleeping", philo->id);
	custom_usleep(philo->time_sleep);
	return (0);
}
