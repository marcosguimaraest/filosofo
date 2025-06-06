/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguimara <mguimara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 20:02:02 by mguimara          #+#    #+#             */
/*   Updated: 2025/04/25 18:12:20 by mguimara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>
# define PHILO 1
# define FORK 2
# define ERROR_CODE 0
# define SUCESS_CODE 1
# define PARSE_CODE 2
# define ALLOC_CODE 3
# define HUMAN_CODE 4
# define THREAD_CODE 5
# define MUTEX_CODE 6
# define ARG_ERROR 7

typedef pthread_mutex_t	mutex_t;

typedef struct s_fork
{
	mutex_t				mutex;
}						t_fork;

typedef struct s_philo
{
	struct timeval		tv;
	int					id;
	pthread_t			thread;
	mutex_t				m_philo;
	long long			last_meal;
	int					is_eating;
	int					times_eat;
}						t_philo;

typedef struct s_table
{
	t_fork				*forks;
	t_philo				*philos;
	pthread_t			t_monitor_death;
	pthread_t			t_monitor_eat;
	int					philo_number;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_to_eat;
	mutex_t				m_philo_number;
	mutex_t				m_time_to_die;
	mutex_t				m_time_to_eat;
	mutex_t				m_time_to_sleep;
	mutex_t				m_number_to_eat;
	int					simulation_ended;
	struct timeval		tv;
}						t_table;

typedef struct s_routine
{
	t_philo				*philo;
	t_table				*table;
}						t_routine;

int						parse_args(int ac, char **av, t_table *table);
int						error_handler(int ecode);
void					*philo_routine(void *table);
int						init_philos(t_table *table);
int						destroy_philos(t_table *table);
int						init_forks(t_table *table);
int						destroy_forks(t_fork *forks);
int						init_table(t_table *table);
int						destroy_table(t_table *table);
void					*ft_calloc(size_t nmemb, size_t size);
long long				get_time_in_miliseconds(struct timeval *tv);
long long				timeval_to_miliseconds(struct timeval *tv);
int						eat(t_philo *philo, t_table *table);
int						take_a_fork(t_philo *philo, t_table *table,
							t_fork *fork);
int						init_monitors(t_table *table);
int						end_simulation(t_philo *philo, t_table *table);
#endif