/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:41:23 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/25 17:48:25 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_sleep(t_philo *philo, t_table *table)
{
    long long   time;

    time = get_time_in_miliseconds(&philo->tv) - timeval_to_miliseconds(&table->tv);
    if (!table->simulation_ended)
    {
        printf("%lld %d is sleeping\n", time, philo->id + 1);
        usleep(table->time_to_sleep * 1000);
    }
}   

static void	p_think(t_philo *philo, t_table *table)
{
    long long   time;

    time = get_time_in_miliseconds(&philo->tv) - timeval_to_miliseconds(&table->tv);
    if (!table->simulation_ended)
        printf("%lld %d is thinking\n", time, philo->id + 1);
}
static void	p_eat(t_philo *philo, t_table *table)
{
    int         left_id;
    int         right_id;

    if (philo->id == 0)
        left_id = table->philo_number - 1;
    else
        left_id = philo->id - 1;
    right_id = philo->id;
	take_a_fork(philo, table, &table->forks[left_id]);  
    take_a_fork(philo, table, &table->forks[right_id]);
    eat(philo, table);
	pthread_mutex_unlock(&table->forks[right_id].mutex);
	pthread_mutex_unlock(&table->forks[left_id].mutex);
}

void	*philo_routine(void *arg)
{
	t_routine	*routine;

	routine = (t_routine *)arg;
    pthread_mutex_lock(&routine->philo->m_philo);
    if (routine->philo->id % 2 == 0)
        usleep(5000);
    routine->philo->last_meal = get_time_in_miliseconds(&routine->philo->tv) - timeval_to_miliseconds(&routine->table->tv);
	while (!routine->table->simulation_ended)
	{
        p_eat(routine->philo, routine->table);
        if (!end_simulation(routine->philo, routine->table))
            return (NULL);
        p_sleep(routine->philo, routine->table);
        if (!end_simulation(routine->philo, routine->table)) 
            return (NULL);
        p_think(routine->philo, routine->table);
	}
	return (NULL);
}
