/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:41:23 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/17 20:01:19 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void		p_sleep(t_philo *philo, t_table *table)
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

static void		p_think(t_philo *philo, t_table *table)
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

static int		get_end(t_table *table)
{
	int	end;

	pthread_mutex_lock(&table->m_simulation_ended);
	end = table->simulation_ended;
	pthread_mutex_unlock(&table->m_simulation_ended);
	return (end);
}

static void		p_eat(t_philo *philo, t_table *table)
{
	int			left_id;
	int			right_id;
	int			l_locked;
	int			r_locked;
	int			ok;

	l_locked = 0;
	r_locked = 0;
	if (philo->id == 0)
		left_id = table->philo_number - 1;
	else
		left_id = philo->id - 1;
	right_id = philo->id;
	if (left_id == right_id)
	{
		ok = take_a_fork(philo, table, &table->forks[left_id]);
		if (ok == SUCESS_CODE)
		{
			usleep(table->time_to_die * 1000);
			pthread_mutex_unlock(&table->forks[left_id].mutex);
		}
		return ;
	}
	ok = take_a_fork(philo, table, &table->forks[left_id]);
	if (ok == SUCESS_CODE)
		l_locked = 1;
	else
		return ;
	if (get_end(table))
		goto cleanup;
	ok = take_a_fork(philo, table, &table->forks[right_id]);
	if (ok == SUCESS_CODE)
		r_locked = 1;
	else
		goto cleanup;
	if (get_end(table))
		goto cleanup;
	ok = eat(philo, table);
cleanup:
	if (r_locked)
		pthread_mutex_unlock(&table->forks[right_id].mutex);
	if (l_locked)
		pthread_mutex_unlock(&table->forks[left_id].mutex);
	(void)ok;
}

void			*philo_routine(void *arg)
{
	t_routine	*routine;
	int			end;

	routine = (t_routine *)arg;
	if (routine->philo->id % 2 == 0)
		usleep(5000);
	pthread_mutex_lock(&routine->philo->m_philo);
	routine->philo->last_meal = get_time_in_miliseconds(&routine->philo->tv)
		- timeval_to_miliseconds(&routine->table->tv);
	pthread_mutex_unlock(&routine->philo->m_philo);
	while (1)
	{
		pthread_mutex_lock(&routine->table->m_simulation_ended);
		end = routine->table->simulation_ended;
		pthread_mutex_unlock(&routine->table->m_simulation_ended);
		if (end)
			break ;
		p_eat(routine->philo, routine->table);
		if (!end_simulation(routine->philo, routine->table))
			break ;
		p_sleep(routine->philo, routine->table);
		if (!end_simulation(routine->philo, routine->table))
			break ;
		p_think(routine->philo, routine->table);
	}
	free(routine);
	return (NULL);
}
