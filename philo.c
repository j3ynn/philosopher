/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbellucc <jbellucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 14:53:14 by jbellucc          #+#    #+#             */
/*   Updated: 2025/07/07 14:53:17 by jbellucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
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
