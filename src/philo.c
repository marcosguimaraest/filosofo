/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:16:51 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/17 23:24:50 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_philos(t_philo *philos)
{
	(void) philos;
	return (SUCESS_CODE);
}

int	init_philos(t_table *table)
{
	int i;

	i = 0;
	table->philos = (t_philo *)ft_calloc(table->philo_number, sizeof(t_philo));
	if (!table->philos)
		return (ALLOC_CODE);
	while (i < table->philo_number)
	{
		table->philos[i].id = i;
		table->philos[i].last_meal = 0;
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
				NULL) != 0)
			return (THREAD_CODE);
		i++;
	}
	return (SUCESS_CODE);
}