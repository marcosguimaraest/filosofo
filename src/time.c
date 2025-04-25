/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:29:13 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/25 14:44:06 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long   timeval_to_miliseconds(struct timeval *tv)
{
    return ((tv->tv_sec * 1000L) + ((tv->tv_usec / 1000L)));
}
long long   get_time_in_miliseconds(struct timeval *tv)
{
    gettimeofday(tv, NULL);
    return (timeval_to_miliseconds(tv));
}
