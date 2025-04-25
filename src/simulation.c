/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:15:01 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/25 17:42:11 by mguimara         ###   ########.fr       */
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

static void  *monitor_number_of_eat(void *arg)
{
    int i;
    int eat;
    t_table *table;

    table = (t_table *) arg;
    eat = 0;
	i = 0;
	while (i < table->philo_number)
	{
		if (table->philos[i].times_eat >= table->number_to_eat)
            eat++;
		i++;
		if (i == table->philo_number)
        {
            if (eat >= table->philo_number)
            {
				table->simulation_ended = 1;
				usleep(5000);
                exit(1);
                return (NULL);
            }
            eat = 0;
            i = 0;
        }
	}
    return (NULL);
}

static void  *monitor_death_philo(void *arg)
{
    int i;
    t_table *table;

    table = (t_table *) arg;
	i = 0;
	while (i < table->philo_number)
	{
		if (!end_simulation(&table->philos[i], table))
		{
            exit(1);
            return (NULL);
        }
		i++;
		if (i == table->philo_number)
			i = 0;
	}
    return (NULL);
}

int	init_monitors(t_table *table)
{
    if (table->number_to_eat >= 0)
        pthread_create(&table->t_monitor_eat, NULL, monitor_number_of_eat, table);
    pthread_create(&table->t_monitor_death, NULL, monitor_death_philo, table);
	return (ERROR_CODE);
}