/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: je <je@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 15:54:06 by jbellucc          #+#    #+#             */
/*   Updated: 2025/06/29 13:58:22 by je               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
	t_data	data;

	if (ac >= 5 && ac <= 6)
	{
		init(&data, ac, av);
		if (check_error(&data))
			return (0);
		alloc_memory(&data);
		init_philo(&data);
		init_forks(&data);
		init_threads(&data);
		free_memory(&data);
	}
	else
	{
		write(2, "Error\n", 6);
		return (0);
	}
}
