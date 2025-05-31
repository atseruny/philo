/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:56:12 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/31 18:01:34 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*eat_count(void *arg)
{
	t_table	*table;
	int		k = 0;

	table = (t_table *)arg;
	while (k < table->num_philo)
	{
		sem_wait(table->meals);
		k++;
	}
	sem_post(table->dead_sem);
	return (NULL);
}

void	*monitor(void *arg)
{
	unsigned long long time;
	int					i;

	i = 0;
	t_philo *philo = (t_philo *)arg;
	while (1)
	{ 
		time = real_time();
		sem_wait(philo->table->last_meal_sem);
		if ((time - philo->last_meal) > philo->table->death_time)
		{
			sem_post(philo->table->last_meal_sem);
			sem_wait(philo->table->print_sem);
			printf("[%llu] %d died\n", time - philo->table->start_time, philo->index);
			sem_post(philo->table->print_sem);
			sem_post(philo->table->dead_sem);
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
