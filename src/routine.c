/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:41:23 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/12 20:01:59 by mguimara         ###   ########.fr       */
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

static void	p_sleep(t_philo *philo, t_table *table)
{
	long long	time;
	int			sim;

	time = get_time_in_miliseconds(&philo->tv)
		- timeval_to_miliseconds(&table->tv);
	sim = sim_ongoing(table);
	if (!sim)
		return ;
	pthread_mutex_lock(&table->m_print);
	if (sim)
		printf("%lld %d is sleeping\n", time, philo->id + 1);
	pthread_mutex_unlock(&table->m_print);
	usleep(table->time_to_sleep * 1000);
}

static void	p_think(t_philo *philo, t_table *table)
{
	long long	time;
	int			sim;

	time = get_time_in_miliseconds(&philo->tv)
		- timeval_to_miliseconds(&table->tv);
	sim = sim_ongoing(table);
	if (!sim)
		return ;
	pthread_mutex_lock(&table->m_print);
	if (sim)
		printf("%lld %d is thinking\n", time, philo->id + 1);
	pthread_mutex_unlock(&table->m_print);
}

static void	p_eat(t_philo *philo, t_table *table)
{
	int	left_id;
	int	right_id;
	int	ok;

	if (philo->id == 0)
		left_id = table->philo_number - 1;
	else
		left_id = philo->id - 1;
	right_id = philo->id;
	if (left_id == right_id)
	{
		if (take_a_fork(philo, table, &table->forks[left_id]) == SUCESS_CODE)
		{
			usleep((table->time_to_die + 1) * 1000);
			pthread_mutex_unlock(&table->forks[left_id].mutex);
		}
		return ;
	}
	ok = take_a_fork(philo, table, &table->forks[left_id]);
	if (ok != SUCESS_CODE)
		return ;
	ok = take_a_fork(philo, table, &table->forks[right_id]);
	if (ok != SUCESS_CODE)
	{
		pthread_mutex_unlock(&table->forks[left_id].mutex);
		return ;
	}
	eat(philo, table);
	pthread_mutex_unlock(&table->forks[right_id].mutex);
	pthread_mutex_unlock(&table->forks[left_id].mutex);
}

void	*philo_routine(void *arg)
{
	t_routine	*routine;

	routine = (t_routine *)arg;
	if (routine->philo->id % 2 == 0)
		usleep(5000);
	pthread_mutex_lock(&routine->philo->m_philo);
	routine->philo->last_meal = get_time_in_miliseconds(&routine->philo->tv)
		- timeval_to_miliseconds(&routine->table->tv);
	pthread_mutex_unlock(&routine->philo->m_philo);
	while (sim_ongoing(routine->table))
	{
		p_eat(routine->philo, routine->table);
		if (!sim_ongoing(routine->table))
			break ;
		p_sleep(routine->philo, routine->table);
		if (!sim_ongoing(routine->table))
			break ;
		p_think(routine->philo, routine->table);
	}
	free(routine);
	return (NULL);
}
