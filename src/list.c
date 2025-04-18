/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:21:26 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/17 22:33:54 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int create_node(void *entity, int entity_code)
{
    t_philo *philo;
    t_fork  *fork;

    if (entity_code == PHILO)
    {
        philo = *((t_philo **) entity);
        philo = (t_philo *) malloc(sizeof(t_philo));
        if (!philo)
            return (ALLOC_CODE);
        pthread_create(philo->thread, NULL, NULL, NULL);
        philo->id = 0;
        philo->last_meal = 0;
        return (SUCESS_CODE);
    }
    fork = *((t_fork **) entity);
    fork = (t_fork *) malloc(sizeof(t_fork));
    fork->id = 0;
}
