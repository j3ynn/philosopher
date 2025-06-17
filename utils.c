/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbellucc <jbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 12:52:41 by jbellucc          #+#    #+#             */
/*   Updated: 2025/06/17 15:27:11 by jbellucc         ###   ########.fr       */
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
	if(data->finish == 1)
		return ;
	printf("%lu %d %s\n", (convert_time() - data->start_time), id, str);
}

int	ft_isdigit(int p)
{
	if (p >= 48 && p <= 57)
		return (1);
	else
		return (0);
}