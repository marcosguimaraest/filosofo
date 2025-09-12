/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:09:24 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/12 14:25:27 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <limits.h>

static int	ft_atoi(const char *s)
{
	int	i;
	int	signal;
	int	result;

	i = 0;
	result = 0;
	signal = 1;
	while (s[i] && (s[i] == ' ' || s[i] == '\f' || s[i] == '\r' || s[i] == '\n'
			|| s[i] == '\t' || s[i] == '\v'))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			signal = -1;
		i++;
	}
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		result = (result * 10) + (s[i] - '0');
		i++;
	}
	return (result * signal);
}

static int	ft_maxint(const char *s)
{
	int			i;
	int			signal;
	long long	result;

	i = -1;
	result = 0;
	signal = 1;
	while (s[i] && (s[i] == ' ' || s[i] == '\f' || s[i] == '\r' || s[i] == '\n'
			|| s[i] == '\t' || s[i] == '\v'))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i++] == '-')
			signal = -1;
	}
	while (s[i] && (s[i] >= '0' && s[i] <= '9'))
	{
		result = (result * 10) + (s[i++] - '0');
		if ((result * signal > (long long)INT_MAX) || (result
				* signal) < (long long)INT_MIN)
			return (-1);
	}
	return (1);
}

int	parse_args(int ac, char **av, t_table *table)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (ft_maxint(av[i]) == -1)
			return (ERROR_CODE);
	}
	table->philo_number = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		table->number_to_eat = ft_atoi(av[5]);
	else
		table->number_to_eat = -1;
	return (SUCESS_CODE);
}
