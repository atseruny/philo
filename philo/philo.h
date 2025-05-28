/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:15:37 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/28 16:19:13 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;
typedef struct s_table	t_table;

struct s_table
{
	int					num_philo;
	int					eat_time;
	int					sleep_time;
	int					must_eat;
	int					dead_philo;
	unsigned long long	death_time;
	unsigned long long	start_time;
	t_philo				**philos;
	pthread_mutex_t		dead;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		**forks;
};

struct s_philo
{
	int					index;
	int					curr_meal;
	int					isdead;
	unsigned long long	last_meal;
	pthread_t			th;
	pthread_mutex_t		last_meal_mutex;
	pthread_mutex_t		curr_meal_mutex;
	pthread_mutex_t		*left;
	pthread_mutex_t		*right;
	t_table				*table;
};

int					ft_isdigit(int c);
int					ft_atol(char *str);
int					ft_strlen(char *str);
unsigned long long	real_time(void);
int					eating(t_philo *philo);
int					sleeping(t_philo *philo);
int					thinking(t_philo *philo);
int					check_if_dead(t_philo *philo);
void				print_mess(t_philo *philo, char *mess);
void				start(t_table *table);
void				usleep_func(t_philo *philo, int time);
void				free_all(t_table *table);
void				*ft_calloc(int count, int size);
void				*monitor(void *arg);

#endif