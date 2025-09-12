/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:15:14 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/12 19:51:43 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_table(t_table *table)
{
	int	i;

	if (!table)
		return (ERROR_CODE);
	// Join monitor threads if they were started
	if (table->t_monitor_death)
		pthread_join(table->t_monitor_death, NULL);
	if (table->t_monitor_eat)
		pthread_join(table->t_monitor_eat, NULL);
	// Join all philosopher threads
	i = 0;
	while (table->philos && i < table->philo_number)
		pthread_join(table->philos[i++].thread, NULL);
	// Destroy and free resources
	destroy_forks(table->forks, table->philo_number);
	destroy_philos(table->philos, table->philo_number);
	pthread_mutex_destroy(&table->m_philo_number);
	pthread_mutex_destroy(&table->m_time_to_die);
	pthread_mutex_destroy(&table->m_time_to_eat);
	pthread_mutex_destroy(&table->m_time_to_sleep);
	pthread_mutex_destroy(&table->m_number_to_eat);
	pthread_mutex_destroy(&table->m_simulation_ended);
	pthread_mutex_destroy(&table->m_print);
	return (SUCESS_CODE);
}

int	init_table(t_table *table)
{
	int	status;

	status = init_forks(table);
	if (status != SUCESS_CODE)
		return (status);
	if (pthread_mutex_init(&table->m_philo_number, NULL) != 0
		|| pthread_mutex_init(&table->m_number_to_eat, NULL) != 0
		|| pthread_mutex_init(&table->m_time_to_die, NULL) != 0
		|| pthread_mutex_init(&table->m_time_to_eat, NULL) != 0
		|| pthread_mutex_init(&table->m_time_to_sleep, NULL) != 0
		|| pthread_mutex_init(&table->m_simulation_ended, NULL) != 0
		|| pthread_mutex_init(&table->m_print, NULL) != 0)
		return (THREAD_CODE);
	pthread_mutex_lock(&table->m_simulation_ended);
	table->simulation_ended = 0;
	pthread_mutex_unlock(&table->m_simulation_ended);
	// Set simulation start time
	gettimeofday(&table->tv, NULL);
	status = init_philos(table);
	if (status != SUCESS_CODE)
		return (status);
	init_monitors(table);
	return (SUCESS_CODE);
}
