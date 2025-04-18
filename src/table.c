/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:15:14 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/18 06:32:26 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int destroy_table(t_table *table)
{
    (void) table;
    return (SUCESS_CODE);
}

int init_table(t_table *table)
{
    int status;

    table->plates_on_table = 0;
    status = init_forks(table);
    if (status != SUCESS_CODE)
        return (status);
    status = init_philos(table);
    if (status != SUCESS_CODE)
        return (status);
    if (pthread_mutex_init(&table->m_philo_number, NULL) != 0 || pthread_mutex_init(&table->m_number_to_eat, NULL) != 0 || pthread_mutex_init(&table->m_time_to_die, NULL) != 0 || pthread_mutex_init(&table->m_time_to_eat, NULL) != 0 || pthread_mutex_init(&table->m_time_to_sleep, NULL) != 0)
        return (THREAD_CODE);
    return (SUCESS_CODE);
}
