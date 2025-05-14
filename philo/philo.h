/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:28:51 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/14 17:36:34 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>


typedef struct s_philo t_philo;
typedef struct s_table t_table;

struct s_table
{
	int				num_philo;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				must_eat;
	int				isdead;
	pthread_mutex_t	*death;
	struct timeval	*start_time;
	t_philo			**philos;
	pthread_mutex_t	**forks;
};

struct s_philo
{
	int				index;
	int				curr_meal;
	int				isdead;
	struct timeval	*ishungry;
	pthread_t		th;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	t_table			*table;
};

int					ft_atoi(char *str);
int					ft_strlen(const char *str);
int					ft_isdigit(int c);
void				start(t_table *table);
unsigned long long	get_time(t_philo *philo);
unsigned long long	real_time(void);
int					is_hungry(t_philo *philo);
int					is_eating(t_philo *philo);
int					is_sleeping(t_philo *philo);
int					is_thinking(t_philo *philo);
void				usleep_func(t_philo *philo, int time);
void				is_dead(t_table *table);
void				free_all(t_table *table);
int					check_if_dead(t_philo *philo);


#endif