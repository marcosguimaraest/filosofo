/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:16:51 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/17 15:21:24 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_philos(t_philo *philos, int len)
{
	int	i;

	i = 0;
	if (!philos)
		return (ERROR_CODE);
	while (i < len)
	{
		pthread_join(philos[i].thread, NULL);
		pthread_mutex_destroy(&philos[i].m_philo);
		i++;
	}
	return (SUCESS_CODE);
}

static int	init_time(t_table *table)
{
	gettimeofday(&table->tv, NULL);
	return (SUCESS_CODE);
}

static int	init_philos_thread(t_table *table)
{
	int			i;
	t_routine	*routine;

	i = 0;
	init_time(table);
	while (i < table->philo_number)
	{
		routine = (t_routine *)ft_calloc(1, sizeof(t_routine));
		if (!routine)
			return (ALLOC_CODE);
		routine->philo = &table->philos[i];
		routine->table = table;
		if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
				(void *)routine) != 0)
			return (THREAD_CODE);
		i++;
	}
	return (SUCESS_CODE);
}

int	init_philos(t_table *table)
{
	int	i;

	i = 0;
	table->philos = (t_philo *)ft_calloc(table->philo_number, sizeof(t_philo));
	if (!table->philos)
		return (ALLOC_CODE);
	while (i < table->philo_number)
	{
		table->philos[i].id = i;
		table->philos[i].is_eating = 0;
		table->philos[i].times_eat = 0;
		pthread_mutex_init(&table->philos[i].m_philo, NULL);
		i++;
	}
	return (init_philos_thread(table));
}
