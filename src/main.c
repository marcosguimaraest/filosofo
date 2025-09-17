/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:08:51 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/17 15:20:47 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 6 || ac == 5)
	{
		if (!parse_args(ac, av, &table))
			return (error_handler(PARSE_CODE));
		init_table(&table);
		while (1)
		{
			pthread_mutex_lock(&table.m_simulation_ended);
			if (table.simulation_ended == 1)
			{
				pthread_mutex_unlock(&table.m_simulation_ended);
				break ;
			}
			pthread_mutex_unlock(&table.m_simulation_ended);
		}
		destroy_table(&table);
	}
	else
		error_handler(ARG_ERROR);
	return (0);
}
