/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:50:26 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/17 15:20:47 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_forks(t_fork *forks, int len)
{
	int	i;

	i = 0;
	if (!forks)
		return (ERROR_CODE);
	while (i < len)
	{
		pthread_mutex_destroy(&forks[i].mutex);
		i++;
	}
	return (SUCESS_CODE);
}

int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	table->forks = (t_fork *)ft_calloc(table->philo_number, sizeof(t_fork));
	if (!table->forks)
		return (ALLOC_CODE);
	while (i < table->philo_number)
	{
		if (pthread_mutex_init(&table->forks[i].mutex, NULL) != 0)
			return (MUTEX_CODE);
		i++;
	}
	return (SUCESS_CODE);
}
