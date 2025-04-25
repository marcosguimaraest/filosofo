/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:08:51 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/25 12:34:10 by mguimara         ###   ########.fr       */
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
        usleep(200);
        while (i < table.philo_number)
        {
            time_now = get_time_in_miliseconds(&tv) - timeval_to_miliseconds(&table.tv);
            // printf("time_now(%lld) - philo[%d] last meal(%lld)\n", time_now, i + 1, table.philos[i].last_meal);
            if ((time_now - table.philos[i].last_meal) > (table.time_to_die) && !table.philos[i].is_eating)
            {
                // printf("time now(%lld) - last_meal(%lld): %lld\n",time_now,table.philos[i].last_meal, (time_now - table.philos[i].last_meal));
                table.simulation_ended = 1;
                usleep(200);
                printf("%lld %d died\n", time_now, i + 1);
                // printf("time-now(%lld) - lastmeal(%lld): %lld || time_to_die: %d\n", time_now, table.philos[i].last_meal, (time_now - table.philos[i].last_meal), table.time_to_die);
                exit(1);
            }
            i++;
            if (i == table.philo_number)
                i = 0;
        }
    }
    else {
        error_handler(ARG_ERROR);
    }   
}