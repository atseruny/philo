/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:31:37 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/13 20:48:39 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_eating(t_philo *philo)
{
	// if (philo->curr_meal == philo->table->must_eat)
	// 	return (1);
	// if (philo->isdead == 1 || philo->table->isdead == 1)
	// 	return (0);
	pthread_mutex_lock(philo->left);
	if (philo->isdead == 1 || philo->table->isdead == 1)
	{
		pthread_mutex_unlock(philo->left);
		return (0);
	}
	printf("[%llu] %d took the left fork\n", get_time(philo), philo->index + 1);
	pthread_mutex_lock(philo->right);
	if (philo->isdead == 1 || philo->table->isdead == 1)
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		return (0);
	}
	printf("[%llu] %d took the right fork\n", get_time(philo), philo->index + 1);
	philo->curr_meal++;
	printf("[%llu] %d is eating\n", get_time(philo), philo->index + 1);
	gettimeofday(philo->ishungry, NULL);
	usleep_func(philo, philo->table->eat_time);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	return (1);
}

int	is_sleeping(t_philo *philo)
{
	if (philo->isdead == 1 || philo->table->isdead == 1)
		return (0);
	printf("[%llu] %d is sleeping\n", get_time(philo), philo->index + 1);
	usleep_func(philo, philo->table->sleep_time);
	return (1);
}

int	is_thinking(t_philo *philo)
{
	if (philo->isdead == 1 || philo->table->isdead == 1)
		return (0);
	printf("[%llu] %d is thinking\n", get_time(philo), philo->index + 1);
	return (1);
}

void	is_dead(t_table *table)
{
	int	i;

	i = 0;
	while (1)
	{
		if (is_hungry(table->philos[i]) > table->death_time)
		{
			pthread_mutex_lock(table->death);
			table->isdead = 1;
			table->philos[i]->isdead = 1;
			pthread_mutex_unlock(table->death);
			printf("[%llu] %d is dead\n", get_time(table->philos[i]), table->philos[i]->index + 1);
			break;
		}
		i = (i + 1) % table->num_philo;
	}
}
