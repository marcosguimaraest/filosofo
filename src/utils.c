/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:37:33 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/17 22:38:58 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*mem;

	if (nmemb > 0 && ((nmemb * size) / nmemb) != size)
		return (NULL);
	mem = malloc(size * nmemb);
	if (!mem)
		return (NULL);
	memset(mem, 0, nmemb * size);
	return (mem);
}