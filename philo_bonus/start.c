/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:27:51 by atseruny          #+#    #+#             */
/*   Updated: 2025/06/01 19:11:55 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	usleep_func(t_philo *philo, int time)
{
	unsigned long long	start;

	start = real_time();
	while (real_time() - start < (unsigned long long)time)
	{
		if (check_if_dead(philo))
			return ;
		usleep(100);
	}
}

void	print_mess(t_philo *philo, char *mess)
{
	sem_wait(philo->table->print_sem);
	if (check_if_dead(philo))
	{
		sem_post(philo->table->print_sem);
		return ;
	}
	printf("[%llu] %d %s", real_time() - philo->table->start_time,
		philo->index, mess);
	sem_post(philo->table->print_sem);
}

void	*life(void *arg)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		usleep_func(philo, philo->table->eat_time - 10);
	while (1)
	{
		if (!eating(philo))
			break;
		if (!sleeping(philo))
			break;
		if (!thinking(philo))
			break;
	}
	return (NULL);
}

void	not_life_yet(t_philo *philo)
{
	pthread_t	death;

	sem_wait(philo->table->last_meal_sem);
	philo->last_meal = philo->table->start_time;
	sem_post(philo->table->last_meal_sem);
	pthread_create(&philo->th, NULL, &life, philo);
	pthread_create(&death, NULL, &monitor, philo);
	pthread_join(philo->th, NULL);
	pthread_join(death, NULL);
	exit (0);
}

void	start(t_table *table)
{
	int		i;
	pthread_t	eat;
	pthread_t	dead;
	
	i = 0;
	table->start_time = real_time();
	while (i < table->num_philo)
	{
		table->philos[i]->pid = fork();
		if (table->philos[i]->pid == -1)
		{
			free_all(table);
			exit (1);
		}
		else if (table->philos[i]->pid == 0)
			not_life_yet(table->philos[i]);
		i++;
	}
	pthread_create(&eat, NULL, &eat_count, table);
	pthread_create(&dead, NULL, &killl, table);
	i = 0;
	while (i < table->num_philo)
		waitpid(table->philos[i++]->pid, NULL, 0);
	pthread_join(eat, NULL);
	pthread_join(dead, NULL);
}

unsigned long long	real_time(void)
{
	struct timeval		now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}
