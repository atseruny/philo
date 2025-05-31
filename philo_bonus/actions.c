/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 14:54:26 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/31 18:01:44 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eating(t_philo *philo)
{
	// if (check_if_dead(philo))
	// 	return (0);
	sem_wait(philo->table->semaphores);
	print_mess(philo, "has taken a fork\n");
	if (philo->table->num_philo == 1)
		return (sem_post(philo->table->semaphores), 0);
	sem_wait(philo->table->semaphores);
	print_mess(philo, "has taken a fork\n");
	print_mess(philo, "is eating\n");
	sem_wait(philo->table->last_meal_sem);
	philo->last_meal = real_time();
	sem_post(philo->table->last_meal_sem);
	usleep_func(philo, philo->table->eat_time);
	sem_wait(philo->table->curr_meal_sem);
	philo->curr_meal++;
	// sem_wait(philo->table->curr_meal_sem);
	if (philo->curr_meal == philo->table->must_eat && philo->has_reported_meal == 0)
	{
		sem_post(philo->table->meals);
		philo->has_reported_meal = 1;
	}
	// sem_post(philo->table->curr_meal_sem);
	sem_post(philo->table->curr_meal_sem);
	sem_post(philo->table->semaphores);
	sem_post(philo->table->semaphores);
	return (1);
}

int	sleeping(t_philo *philo)
{
	// if (check_if_dead(philo))
	// 	return (0);
	print_mess(philo, "is sleeping\n");
	usleep_func(philo, philo->table->sleep_time);
	return (1);
}

int	thinking(t_philo *philo)
{
	// if (check_if_dead(philo))
	// 	return (0);
	print_mess(philo, "is thinking\n");
	return (1);
}
