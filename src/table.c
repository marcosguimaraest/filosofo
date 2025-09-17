/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:15:14 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/17 14:45:38 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				destroy_table(t_table *table)
{
	if (!table)
		return (ERROR_CODE);
	if (table->t_monitor_death)
		pthread_join(table->t_monitor_death, NULL);
	if (table->t_monitor_eat)
		pthread_join(table->t_monitor_eat, NULL);
	destroy_philos(table->philos, table->philo_number);
	destroy_forks(table->forks, table->philo_number);
	pthread_mutex_destroy(&table->m_print);
	pthread_mutex_destroy(&table->m_philo_number);
	pthread_mutex_destroy(&table->m_time_to_die);
	pthread_mutex_destroy(&table->m_time_to_eat);
	pthread_mutex_destroy(&table->m_time_to_sleep);
	pthread_mutex_destroy(&table->m_number_to_eat);
	pthread_mutex_destroy(&table->m_simulation_ended);
	free(table->philos);
	free(table->forks);
	return (SUCESS_CODE);
}

int				init_table(t_table *table)
{
	int	status;

	/* init shared mutexes before any threads start */
	if (pthread_mutex_init(&table->m_print, NULL) != 0
		|| pthread_mutex_init(&table->m_philo_number, NULL) != 0
		|| pthread_mutex_init(&table->m_number_to_eat, NULL) != 0
		|| pthread_mutex_init(&table->m_time_to_die, NULL) != 0
		|| pthread_mutex_init(&table->m_time_to_eat, NULL) != 0
		|| pthread_mutex_init(&table->m_time_to_sleep, NULL) != 0
		|| pthread_mutex_init(&table->m_simulation_ended, NULL) != 0)
		return (THREAD_CODE);
	table->simulation_ended = 0;
	status = init_forks(table);
	if (status != SUCESS_CODE)
		return (status);
	status = init_philos(table);
	if (status != SUCESS_CODE)
		return (status);
	init_monitors(table);
	return (SUCESS_CODE);
}
