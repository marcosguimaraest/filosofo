/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:15:01 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/17 14:50:40 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int				end_simulation(t_philo *philo, t_table *table)
{
	struct timeval										tv;
	long long											time_now;
	long long											last_meal;
	int													is_eating;
	int													need_print;

	time_now = get_time_in_miliseconds(&tv)
		- timeval_to_miliseconds(&table->tv);
	pthread_mutex_lock(&philo->m_philo);
	last_meal = philo->last_meal;
	is_eating = philo->is_eating;
	pthread_mutex_unlock(&philo->m_philo);
	if (((time_now - last_meal) >= table->time_to_die) && !is_eating)
	{
		need_print = 0;
		pthread_mutex_lock(&table->m_simulation_ended);
		if (table->simulation_ended == 0)
		{
			table->simulation_ended = 1;
			need_print = 1;
		}
		pthread_mutex_unlock(&table->m_simulation_ended);
		if (need_print)
		{
			pthread_mutex_lock(&table->m_print);
			printf("%lld %d died\n", time_now, philo->id + 1);
			pthread_mutex_unlock(&table->m_print);
		}
		return (ERROR_CODE);
	}
	pthread_mutex_lock(&table->m_simulation_ended);
	if (table->simulation_ended == 1)
	{
		pthread_mutex_unlock(&table->m_simulation_ended);
		return (ERROR_CODE);
	}
	pthread_mutex_unlock(&table->m_simulation_ended);
	return (SUCESS_CODE);
}

static void		*monitor_number_of_eat(void *arg)
{
	int										i;
	int										eat;
	t_table									*table;

	table = (t_table *)arg;
	eat = 0;
	i = 0;
	while (i < table->philo_number)
	{
		pthread_mutex_lock(&table->philos[i].m_philo);
		if (table->philos[i].times_eat >= table->number_to_eat)
			eat++;
		pthread_mutex_unlock(&table->philos[i].m_philo);
		i++;
		if (i == table->philo_number)
		{
			if (eat >= table->philo_number)
			{
				pthread_mutex_lock(&table->m_simulation_ended);
				table->simulation_ended = 1;
				pthread_mutex_unlock(&table->m_simulation_ended);
				usleep(5000);
				return (NULL);
			}
			eat = 0;
			i = 0;
		}
	}
	return (NULL);
}

static void		*monitor_death_philo(void *arg)
{
	int										i;
	t_table									*table;

	table = (t_table *)arg;
	i = 0;
	while (i < table->philo_number)
	{
		if (!end_simulation(&table->philos[i], table))
			return (NULL);
		i++;
		if (i == table->philo_number)
			i = 0;
	}
	return (NULL);
}

int				init_monitors(t_table *table)
{
	if (table->number_to_eat >= 0)
		pthread_create(&table->t_monitor_eat, NULL,
			monitor_number_of_eat, table);
	else
		table->t_monitor_eat = 0;
	pthread_create(&table->t_monitor_death, NULL, monitor_death_philo, table);
	return (ERROR_CODE);
}
