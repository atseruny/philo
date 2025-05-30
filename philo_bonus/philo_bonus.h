/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:15:37 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/30 18:42:12 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>


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
	sem_t				*semaphores;
	sem_t				*print_sem;
	sem_t				*dead_sem;
	sem_t				*dead_check;
	sem_t				*curr_meal_sem;
	sem_t				*last_meal_sem;
	t_philo				**philos;
};

struct s_philo
{
	int					index;
	int					curr_meal;
	int					isdead;
	unsigned long long	last_meal;
	pthread_t			th;
	pid_t				pid;
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