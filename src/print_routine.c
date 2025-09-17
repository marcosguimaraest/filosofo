/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:41:11 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/17 19:58:12 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				take_a_fork(t_philo *philo, t_table *table, t_fork *fork)
{
	long long	time;
	int			end;

	pthread_mutex_lock(&table->m_simulation_ended);
	end = table->simulation_ended;
	pthread_mutex_unlock(&table->m_simulation_ended);
	if (end)
		return (ERROR_CODE);
	pthread_mutex_lock(&fork->mutex);
	/* re-check after acquiring the fork to avoid post-death prints */
	pthread_mutex_lock(&table->m_simulation_ended);
	end = table->simulation_ended;
	pthread_mutex_unlock(&table->m_simulation_ended);
	if (end)
	{
		pthread_mutex_unlock(&fork->mutex);
		return (ERROR_CODE);
	}
	time = get_time_in_miliseconds(&philo->tv)
		- timeval_to_miliseconds(&table->tv);
	pthread_mutex_lock(&table->m_print);
	printf("%lld %d has taken a fork\n", time, philo->id + 1);
	pthread_mutex_unlock(&table->m_print);
	return (SUCESS_CODE);
}

int				eat(t_philo *philo, t_table *table)
{
	long long	time;
	int			end;

	pthread_mutex_lock(&table->m_simulation_ended);
	end = table->simulation_ended;
	pthread_mutex_unlock(&table->m_simulation_ended);
	if (end)
		return (ERROR_CODE);
	time = get_time_in_miliseconds(&philo->tv)
		- timeval_to_miliseconds(&table->tv);
	pthread_mutex_lock(&philo->m_philo);
	philo->last_meal = time;
	philo->is_eating = 1;
	pthread_mutex_unlock(&philo->m_philo);
	pthread_mutex_lock(&table->m_print);
	printf("%lld %d is eating\n", time, philo->id + 1);
	pthread_mutex_unlock(&table->m_print);
	usleep(table->time_to_eat * 1000);
	pthread_mutex_lock(&philo->m_philo);
	philo->is_eating = 0;
	philo->times_eat++;
	pthread_mutex_unlock(&philo->m_philo);
	return (SUCESS_CODE);
}
