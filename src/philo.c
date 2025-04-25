/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:16:51 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/25 14:29:53 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_philos(t_philo *philos)
{
	(void)philos;
	return (SUCESS_CODE);
}
static int	unlock_philos(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->philo_number)
	{
		pthread_mutex_unlock(&table->philos[i].m_philo);
		usleep(100);
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
	while (i < table->philo_number)
	{
		routine = (t_routine *) ft_calloc(table->philo_number, sizeof(t_routine));
		if (!routine)
			return (ALLOC_CODE);
		routine[i].philo = &table->philos[i];
		routine[i].table = table;
		pthread_mutex_lock(&table->philos[i].m_philo);
		pthread_create(&table->philos[i].thread, NULL, philo_routine,
				&routine[i]);
		// if (pthread_create(&table->philos[i].thread, NULL, philo_routine,
		// 		&routine) != 0)
		// 	return (THREAD_CODE);
		init_time(table);
		i++;
	}
	unlock_philos(table);
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
		table->philos[i].is_eating = 0;
		pthread_mutex_init(&table->philos[i].m_philo, NULL);
		// printf("philo %d criado %ld\n", i, table->philos[i].tv.tv_sec);
		i++;
	}
	return (init_philos_thread(table));
}