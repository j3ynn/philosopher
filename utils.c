
#include "philo.h"

int	ft_atoi(const char *str)
{
	int p;
	int ris;

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
