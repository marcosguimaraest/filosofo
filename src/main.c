/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:08:51 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/18 07:25:58 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_table     table;
    struct timeval     tv;
    int         i;
    long long   time_now;

    i = 0;
    if (ac == 6 || ac == 5)
    {
        if (!parse_args(ac, av, &table))
            return (error_handler(PARSE_CODE));
        init_table(&table);
        while (i < table.philo_number)
        {
            // printf("i: %d\n", i);
            gettimeofday(&tv, NULL);
            time_now = ((long long) tv.tv_sec) * 1000;
            // pthread_mutex_lock(&table.philos[i].m_philo);
            if ((time_now - table.philos[i].last_meal) > (table.time_to_die + table.time_to_sleep + table.time_to_eat))
            {
                printf("%lld %d is dead\n time-now - lastmeal: %lld || time_to_die + eat: %d", time_now, i + 1, (time_now - table.philos[i].last_meal), (table.time_to_die + table.time_to_sleep + table.time_to_eat));
                exit(1);
            }
            // pthread_mutex_unlock(&table.philos[i].m_philo);
            i++;
            if (i == table.philo_number)
                i = 0;
        }
    }
    else {
        error_handler(ARG_ERROR);
    }   
}