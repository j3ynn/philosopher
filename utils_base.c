/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbellucc <jbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:54:49 by jbellucc          #+#    #+#             */
/*   Updated: 2025/07/17 17:02:54 by jbellucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int i)
{
	if (i >= 48 && i <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	p;
	int	ris;

	p = 0;
	ris = 0;
	while ((str[p] == ' ') || (str[p] >= 9 && str[p] <= 13))
		p++;
	if (str[p] == '-')
		return (-1);
	if (!ft_isdigit(str[p]))
		return (-1);
	while (ft_isdigit(str[p]))
	{
		if (ris > (2147483647 - (str[p] - 48)) / 10)
			return (-1);
		ris = ris * 10 + (str[p] - 48);
		p++;
	}
	if (str[p] != '\0')
		return (-1);
	return (ris);
}

int	check_error(t_data *data)
{
	if (data->num_philos < 0 || data->num_eat < 0)
	{
		write(2, "Error\n", 6);
		return (1);
	}
	return (0);
}

void	print_status(t_data *data, char *str, int id)
{
	pthread_mutex_lock(&data->lock);
	if (data->finish == 0)
		printf("%lu %d %s\n", (convert_time() - data->start_time), id, str);
	pthread_mutex_unlock(&data->lock);
}
