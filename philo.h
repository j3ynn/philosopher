
#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct	s_philo
{
	struct s_data	*data;
    int				id;
	int				time_eat;
	int				time_sleep;
	int				time_die;
	int				num_eaten;
	bool			dead;
	pthread_t		thread;
	uint64_t		time_to_die;
	pthread_mutex_t	*fork_s;
	pthread_mutex_t	*fork_d;
	pthread_mutex_t	lock;
}	t_philo;

typedef struct	s_data
{
	int				num_philos;
	int				num_eat;
	int				finish;
	t_philo			*philo;
	uint64_t		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	lock;
	pthread_mutex_t	print;
}	t_data;

uint64_t	convert_time(void);

int			ft_isdigit(int i);
int			ft_atoi(const char *str);
int			check_error(t_data *data);

void		print_status(t_data *data, char *str, int id);
void		alloc_memory(t_data *data);
void		free_memory(t_data *data);

#endif
