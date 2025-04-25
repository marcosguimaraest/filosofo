/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:15:01 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/25 14:30:25 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	end_simulation(t_philo *philo, t_table *table)
{
	struct timeval	tv;
	long long		time_now;

	time_now = get_time_in_miliseconds(&tv)
		- timeval_to_miliseconds(&table->tv);
	if (((time_now - philo->last_meal) >= table->time_to_die)
		&& !philo->is_eating)
	{
		table->simulation_ended = 1;
		usleep(200);
		printf("%lld %d died\n", time_now, philo->id + 1);
		return (ERROR_CODE);
	}
	if (table->simulation_ended == 1)
		return (ERROR_CODE);
	return (SUCESS_CODE);
}

int	start_monitoring(t_table *table)
{
	int i;

	i = 0;
	while (i < table->philo_number)
	{
		if (!end_simulation(&table->philos[i], table))
			return (SUCESS_CODE);
		i++;
		if (i == table->philo_number)
			i = 0;
	}
	return (ERROR_CODE);
}