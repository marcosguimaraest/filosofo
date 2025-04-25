/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:08:51 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/25 15:15:27 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_table     table;

    if (ac == 6 || ac == 5)
    {
        if (!parse_args(ac, av, &table))
            return (error_handler(PARSE_CODE));
        init_table(&table);
        init_monitors(&table);
        while (1)
            ;
    }
    else {
        error_handler(ARG_ERROR);
    }   
}