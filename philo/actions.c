/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:26 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/26 20:00:29 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	taking_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_lock(philo->left);
		print_mess(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->right);
		print_mess(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->right);
		print_mess(philo, "has taken a fork\n");
		if (philo->table->num_philo == 1)
		{
			pthread_mutex_unlock(philo->right);
			return (0);
		}
		pthread_mutex_lock(philo->left);
		print_mess(philo, "has taken a fork\n");
	}
	return (1);
}

void	puting_forks(t_philo *philo)
{
	if (philo->index % 2 == 0)
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
	}
	else
	{
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(philo->left);
	}
}

int	eating(t_philo *philo)
{
	if (check_if_dead(philo) == 1)
		return (0);
	if (taking_forks(philo) == 0)
		return (0);
	pthread_mutex_lock(&philo->curr_meal_mutex);
	philo->curr_meal++;
	pthread_mutex_unlock(&philo->curr_meal_mutex);
	print_mess(philo, "is eating\n");
	pthread_mutex_lock(&philo->last_meal_mutex);
	philo->last_meal = real_time();
	pthread_mutex_unlock(&philo->last_meal_mutex);
	usleep_func(philo, philo->table->eat_time);
	puting_forks(philo);
	pthread_mutex_lock(&philo->curr_meal_mutex);
	if (philo->curr_meal == philo->table->must_eat)
	{
		pthread_mutex_unlock(&philo->curr_meal_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->curr_meal_mutex);

	return (1);
}

int	sleeping(t_philo *philo)
{
	if (check_if_dead(philo) == 1)
		return (0);
	print_mess(philo, "is sleeping\n");
	usleep_func(philo, philo->table->sleep_time);
	return (1);
}

int	thinking(t_philo *philo)
{
	if (check_if_dead(philo) == 1)
		return (0);
	print_mess(philo, "is thinking\n");
	return (1);
}
