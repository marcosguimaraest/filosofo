/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 19:59:00 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/17 15:21:17 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_end(t_table *table)
{
	int	end;

	pthread_mutex_lock(&table->m_simulation_ended);
	end = table->simulation_ended;
	pthread_mutex_unlock(&table->m_simulation_ended);
	return (end);
}

static void	set_end(t_table *table)
{
	pthread_mutex_lock(&table->m_simulation_ended);
	table->simulation_ended = 1;
	pthread_mutex_unlock(&table->m_simulation_ended);
}

static void	*monitor_number_of_eat(void *arg)
{
	int		i;
	int		eat;
	t_table	*table;

	table = (t_table *)arg;
	while (!get_end(table))
	{
		eat = 0;
		i = 0;
		while (i < table->philo_number)
		{
			pthread_mutex_lock(&table->philos[i].m_philo);
			if (table->philos[i].times_eat >= table->number_to_eat)
				eat++;
			pthread_mutex_unlock(&table->philos[i].m_philo);
			i++;
		}
		if (eat >= table->philo_number)
		{
			set_end(table);
			return (NULL);
		}
	}
	return (NULL);
}

static void	*monitor_death_philo(void *arg)
{
	int		i;
	t_table	*table;

	table = (t_table *)arg;
	while (!get_end(table))
	{
		i = 0;
		while (i < table->philo_number)
		{
			if (!end_simulation(&table->philos[i], table))
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

int	init_monitors(t_table *table)
{
	if (table->number_to_eat >= 0)
		pthread_create(&table->t_monitor_eat, NULL, monitor_number_of_eat,
			table);
	else
		table->t_monitor_eat = 0;
	pthread_create(&table->t_monitor_death, NULL, monitor_death_philo, table);
	return (ERROR_CODE);
}
