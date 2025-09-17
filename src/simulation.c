/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:15:01 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/17 15:21:35 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	should_die(t_philo *philo, t_table *table, long long now)
{
	long long	last_meal;
	int			is_eating;

	pthread_mutex_lock(&philo->m_philo);
	last_meal = philo->last_meal;
	is_eating = philo->is_eating;
	pthread_mutex_unlock(&philo->m_philo);
	return (((now - last_meal) >= table->time_to_die) && !is_eating);
}

static int	set_end_once(t_table *table)
{
	int	printed;

	printed = 0;
	pthread_mutex_lock(&table->m_simulation_ended);
	if (table->simulation_ended == 0)
	{
		table->simulation_ended = 1;
		printed = 1;
	}
	pthread_mutex_unlock(&table->m_simulation_ended);
	return (printed);
}

static int	get_end(t_table *table)
{
	int	end;

	pthread_mutex_lock(&table->m_simulation_ended);
	end = table->simulation_ended;
	pthread_mutex_unlock(&table->m_simulation_ended);
	return (end);
}

static void	print_died(t_table *table, int id, long long now)
{
	pthread_mutex_lock(&table->m_print);
	printf("%lld %d died\n", now, id + 1);
	pthread_mutex_unlock(&table->m_print);
}

int	end_simulation(t_philo *philo, t_table *table)
{
	struct timeval	tv;
	long long		now;

	now = get_time_in_miliseconds(&tv) - timeval_to_miliseconds(&table->tv);
	if (should_die(philo, table, now))
	{
		if (set_end_once(table))
			print_died(table, philo->id, now);
		return (ERROR_CODE);
	}
	if (get_end(table))
		return (ERROR_CODE);
	return (SUCESS_CODE);
}
