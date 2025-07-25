/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:56:12 by atseruny          #+#    #+#             */
/*   Updated: 2025/06/03 20:25:54 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long long	real_time(void)
{
	struct timeval		now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}

void	*killl(void *arg)
{
	int		i;
	t_table	*table;

	table = (t_table *)arg;
	sem_wait(table->dead_sem);
	i = 0;
	while (i < table->num_philo)
	{
		sem_post(table->meals);
		kill(table->philos[i++]->pid, SIGKILL);
	}
	return (NULL);
}

void	*eat_count(void *arg)
{
	t_table	*table;
	int		i;

	i = 0;
	table = (t_table *)arg;
	if (table->must_eat == -1)
		return (NULL);
	while (i < table->num_philo)
	{
		if (check_if_dead(table->philos[i]))
			return (NULL);
		sem_wait(table->meals);
		i++;
	}
	sem_post(table->dead_sem);
	return (NULL);
}

void	*monitor(void *arg)
{
	unsigned long long	time;
	t_philo				*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		time = real_time();
		sem_wait(philo->table->last_meal_sem);
		if ((time - philo->last_meal) > philo->table->death_time)
		{
			sem_post(philo->table->last_meal_sem);
			sem_post(philo->table->dead_sem);
			sem_wait(philo->table->print_sem);
			printf("[%llu] %d is dead\n", time - philo->table->start_time,
				philo->index);
			sem_wait(philo->table->dead_check);
			philo->table->dead_philo = 1;
			philo->isdead = 1;
			sem_post(philo->table->dead_check);
			return (NULL);
		}
		sem_post(philo->table->last_meal_sem);
		usleep(500);
	}
	return (NULL);
}

int	check_if_dead(t_philo *philo)
{
	int	i;

	i = 1;
	sem_wait(philo->table->dead_check);
	if (philo->isdead == 0 && philo->table->dead_philo == 0)
		i = 0;
	sem_post(philo->table->dead_check);
	return (i);
}
