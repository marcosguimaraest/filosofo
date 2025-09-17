/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 21:45:00 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/17 15:38:06 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_end_flag(t_table *table)
{
	int	end;

	pthread_mutex_lock(&table->m_simulation_ended);
	end = table->simulation_ended;
	pthread_mutex_unlock(&table->m_simulation_ended);
	return (end);
}

void	cleanup_locks(t_table *table, int left_id, int right_id, int l_locked)
{
	if (right_id >= 0)
		pthread_mutex_unlock(&table->forks[right_id].mutex);
	if (l_locked)
		pthread_mutex_unlock(&table->forks[left_id].mutex);
}

int	single_philo_block(t_philo *philo, t_table *table, int fork_id)
{
	int	ok;

	ok = take_a_fork(philo, table, &table->forks[fork_id]);
	if (ok == SUCESS_CODE)
	{
		usleep(table->time_to_die * 1000);
		pthread_mutex_unlock(&table->forks[fork_id].mutex);
	}
	return (ok);
}

int	get_left_id(int philo_number, int id)
{
	if (id == 0)
		return (philo_number - 1);
	return (id - 1);
}
