/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 22:10:16 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/17 23:03:14 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_all(void)
{
	printf("Destroy all");
}

static void	print_strerr(char *s)
{
	while (*s)
		write(STDERR_FILENO, &(*(s++)), 1);
}

int	error_handler(int ecode)
{
	if (ecode == PARSE_CODE)
		print_strerr("Parse error\n");
	else if (ecode == HUMAN_CODE)
		print_strerr("Human error\n");
	else if (ecode == ALLOC_CODE)
		print_strerr("Allocation error\n");
	else if (ecode == THREAD_CODE)
		print_strerr("Thread error\n");
	else if (ecode == MUTEX_CODE)
		print_strerr("Mutex error\n");
	else if (ecode == ARG_ERROR)
		print_strerr("Argument number error\n");
	destroy_all();
	return (ecode);
}