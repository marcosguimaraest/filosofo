/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:15:14 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/17 23:11:00 by mguimara         ###   ########.fr       */
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

    status = init_philos(table);
    if (status != SUCESS_CODE)
        return (status);
    status = init_forks(table);
    if (status != SUCESS_CODE)
        return (status);
    return (SUCESS_CODE);
}
