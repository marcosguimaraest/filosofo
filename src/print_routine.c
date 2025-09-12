/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:41:11 by mguimara          #+#    #+#             */
/*   Updated: 2025/09/12 15:47:42 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_a_fork(t_philo *philo, t_table *table, t_fork *fork)
{
	long long	time;

	if (!table->simulation_ended)
	{
		pthread_mutex_lock(&fork->mutex);
		time = get_time_in_miliseconds(&philo->tv)
			- timeval_to_miliseconds(&table->tv);
		printf("%lld %d has taken a fork\n", time, philo->id + 1);
		return (SUCESS_CODE);
	}
	return (ERROR_CODE);
}

int	eat(t_philo *philo, t_table *table)
{
	long long	time;

	if (!table->simulation_ended)
	{
		time = get_time_in_miliseconds(&philo->tv)
			- timeval_to_miliseconds(&table->tv);
		philo->last_meal = time;
		philo->is_eating = 1;
		printf("%lld %d is eating\n", time, philo->id + 1);
		usleep(table->time_to_eat * 1000);
		philo->is_eating = 0;
		philo->times_eat++;
		return (SUCESS_CODE);
	}
	return (ERROR_CODE);
}
