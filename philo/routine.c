/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:31:37 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/18 20:54:12 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *mess)
{
	if (check_if_dead(philo) == 1)
		return ;
	printf("[%lld] %d %s\n", real_time() - philo->table->start_time,
		philo->index + 1, mess);
}

int	taking_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->left);
		print_message(philo, "has taken a fork");
		if (philo->table->num_philo == 1)
		{
			pthread_mutex_unlock(philo->left);
			return (0);
		}
		pthread_mutex_lock(philo->right);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->left);
		print_message(philo, "has taken a fork");
	}
	return (1);
}

int	is_eating(t_philo *philo)
{
	if (philo->curr_meal == philo->table->must_eat)
	{
		(philo->table->kusht)++;
		return (0);
	}
	if (check_if_dead(philo) == 1 || taking_forks(philo) == 0)
		return (0);
	philo->curr_meal++;
	print_message(philo, "is eating");
	philo->ishungry = real_time();
	usleep_func(philo, philo->table->eat_time);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
	return (1);
}

int	is_sleeping(t_philo *philo)
{
	if (check_if_dead(philo) == 1)
		return (0);
	print_message(philo, "is sleeping");
	usleep_func(philo, philo->table->sleep_time);
	return (1);
}

int	is_thinking(t_philo *philo)
{
	if (check_if_dead(philo) == 1)
		return (0);
	print_message(philo, "is thinking");
	return (1);
}
