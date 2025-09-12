/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:41:11 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/12 19:51:45 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	sim_ongoing(t_table *table)
{
	int	v;

	pthread_mutex_lock(&table->m_simulation_ended);
	v = (table->simulation_ended == 0);
	pthread_mutex_unlock(&table->m_simulation_ended);
	return (v);
}

int	take_a_fork(t_philo *philo, t_table *table, t_fork *fork)
{
	long long	time;

	if (!sim_ongoing(table))
		return (ERROR_CODE);
	pthread_mutex_lock(&fork->mutex);
	time = get_time_in_miliseconds(&philo->tv)
		- timeval_to_miliseconds(&table->tv);
	pthread_mutex_lock(&table->m_print);
	if (sim_ongoing(table))
		printf("%lld %d has taken a fork\n", time, philo->id + 1);
	pthread_mutex_unlock(&table->m_print);
	return (SUCESS_CODE);
}

int	eat(t_philo *philo, t_table *table)
{
	long long	time;

	if (!sim_ongoing(table))
		return (ERROR_CODE);
	time = get_time_in_miliseconds(&philo->tv)
		- timeval_to_miliseconds(&table->tv);
	pthread_mutex_lock(&philo->m_philo);
	philo->last_meal = time;
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->m_philo);
	pthread_mutex_lock(&table->m_print);
	if (sim_ongoing(table))
		printf("%lld %d is eating\n", time, philo->id + 1);
	pthread_mutex_unlock(&table->m_print);
	usleep(table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->m_philo);
	philo->is_eating = 0;
	philo->times_eat++;
	pthread_mutex_unlock(&philo->m_philo);
	return (SUCESS_CODE);
}
