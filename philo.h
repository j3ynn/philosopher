/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: je <je@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 11:00:18 by jbellucc          #+#    #+#             */
/*   Updated: 2025/06/29 14:24:16 by je               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
	int				eating;
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
	int				finish;
	int				num_eat;
	int				time_die;
	int				time_eat;
	int				time_sleep;
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
int			custom_usleep(uint16_t time);
int			one_fork(t_philo *philo);
int			philo_sleep(t_philo *philo);
int			check_dead(t_data *data, int i);

void		print_status(t_data *data, char *str, int id);
void		alloc_memory(t_data *data);
void		free_memory(t_data *data);
void		timer_to_die(void *p);
void		philo_eat(t_philo *philo);
void		*philo_routine(void *arg);
void		init_philo(t_data *data);
void		init_forks(t_data *data);
void		init_threads(t_data *data);
void		init(t_data *data, int ac, char **av);
void		philo_sated(t_philo *philo);

void	*monitor_death(void *arg);

#endif
