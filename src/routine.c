/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:41:23 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/17 15:36:21 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_sleep(t_philo *philo, t_table *table)
{
	long long	time;
	int			end;

	time = get_time_in_miliseconds(&philo->tv)
		- timeval_to_miliseconds(&table->tv);
	pthread_mutex_lock(&table->m_simulation_ended);
	end = table->simulation_ended;
	pthread_mutex_unlock(&table->m_simulation_ended);
	if (!end)
	{
		pthread_mutex_lock(&table->m_print);
		printf("%lld %d is sleeping\n", time, philo->id + 1);
		pthread_mutex_unlock(&table->m_print);
		usleep(table->time_to_sleep * 1000);
	}
}

static void	p_think(t_philo *philo, t_table *table)
{
	long long	time;
	int			end;

	time = get_time_in_miliseconds(&philo->tv)
		- timeval_to_miliseconds(&table->tv);
	pthread_mutex_lock(&table->m_simulation_ended);
	end = table->simulation_ended;
	pthread_mutex_unlock(&table->m_simulation_ended);
	if (!end)
	{
		pthread_mutex_lock(&table->m_print);
		printf("%lld %d is thinking\n", time, philo->id + 1);
		pthread_mutex_unlock(&table->m_print);
	}
}

static void	lock_left_first(t_philo *philo, t_table *table, int left_id,
		int *l_locked)
{
	int	ok;

	ok = take_a_fork(philo, table, &table->forks[left_id]);
	if (ok == SUCESS_CODE)
		*l_locked = 1;
}

static void	p_eat(t_philo *philo, t_table *table)
{
	int	left_id;
	int	right_id;
	int	l_locked;
	int	r_locked;

	l_locked = 0;
	r_locked = 0;
	left_id = get_left_id(table->philo_number, philo->id);
	right_id = philo->id;
	if (left_id == right_id)
	{
		single_philo_block(philo, table, left_id);
		return ;
	}
	lock_left_first(philo, table, left_id, &l_locked);
	if (!l_locked || get_end_flag(table))
		return (cleanup_locks(table, left_id, -1, l_locked));
	if (take_a_fork(philo, table, &table->forks[right_id]) == SUCESS_CODE)
		r_locked = 1;
	if (!r_locked || get_end_flag(table))
		return (cleanup_locks(table, left_id, right_id, l_locked));
	eat(philo, table);
	cleanup_locks(table, left_id, right_id, l_locked);
}

void	*philo_routine(void *arg)
{
	t_routine	*r;

	r = (t_routine *)arg;
	if (r->philo->id % 2 == 0)
		usleep(5000);
	pthread_mutex_lock(&r->philo->m_philo);
	r->philo->last_meal = get_time_in_miliseconds(&r->philo->tv)
		- timeval_to_miliseconds(&r->table->tv);
	pthread_mutex_unlock(&r->philo->m_philo);
	while (!get_end_flag(r->table))
	{
		p_eat(r->philo, r->table);
		if (!end_simulation(r->philo, r->table))
			break ;
		p_sleep(r->philo, r->table);
		if (!end_simulation(r->philo, r->table))
			break ;
		p_think(r->philo, r->table);
	}
	free(r);
	return (NULL);
}
