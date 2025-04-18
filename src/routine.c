/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:41:23 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/18 07:30:30 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	p_sleep(t_philo *philo, t_table *table)
{
    // char    id;

    // id = (philo->id + 1) + 'a';
    // write(STDOUT_FILENO, &id, 1);
    // write(STDOUT_FILENO, " dormiu\n", 7);
    (void) table;
    gettimeofday(&philo->tv, NULL);
    printf("%ld %d is sleeping\n", philo->tv.tv_sec * 1000, philo->id + 1);
    usleep(table->time_to_sleep * 1000);
}   

static void	p_think(t_philo *philo)
{
    gettimeofday(&philo->tv, NULL);
    printf("%ld %d is thinking\n", philo->tv.tv_sec * 1000, philo->id + 1);
}
static void	p_eat(t_philo *philo, t_table *table)
{
    int left_id;
    int right_id;

    // pthread_mutex_lock(&philo->m_philo);
    if (philo->id == 0)
        left_id = table->philo_number - 1;
    else
        left_id = philo->id - 1;
    right_id = philo->id;
    // printf("philo %d will try to get fork %d\n", philo->id + 1, left_id + 1);
	pthread_mutex_lock(&table->forks[left_id].mutex);
    gettimeofday(&philo->tv, NULL);
    printf("%ld %d has taken a fork\n", philo->tv.tv_sec * 1000, philo->id + 1);
    // printf("philo %d will try to get fork %d\n", philo->id + 1, right_id + 1);
    pthread_mutex_lock(&table->forks[right_id].mutex);
    gettimeofday(&philo->tv, NULL);
    printf("%ld %d has taken a fork\n", philo->tv.tv_sec * 1000, philo->id + 1);
    gettimeofday(&philo->tv, NULL);
    philo->last_meal =  philo->tv.tv_sec * 1000;
    printf("%lld %d is eating\n", philo->last_meal, philo->id + 1);
    // pthread_mutex_unlock(&philo->m_philo);
    usleep(table->time_to_eat * 1000);
	pthread_mutex_unlock(&table->forks[right_id].mutex);
	pthread_mutex_unlock(&table->forks[left_id].mutex);
}

void	*philo_routine(void *arg)
{
	t_routine	*routine;

	routine = (t_routine *)arg;
    // printf("i am %d\n", routine->philo->id + 1);
    while (routine->table->plates_on_table == 0)
        usleep(0);
    ;
	while (1)
	{
        p_eat(routine->philo, routine->table);
        p_sleep(routine->philo, routine->table);
        p_think(routine->philo);
	}
	return (NULL);
}
