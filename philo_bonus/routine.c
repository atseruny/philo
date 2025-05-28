/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:56:12 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/28 21:01:44 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	eat_count(t_table *table)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (i < table->num_philo)
	{
		sem_wait(table->curr_meal_sem);
		if (table->must_eat != -1 && table->philos[i]->curr_meal >= table->must_eat)
			k++;
		sem_post(table->curr_meal_sem);
		i++;
		usleep(50);
	}
	if (k == table->num_philo)
	{
		sem_wait(table->dead_sem);
		table->dead_philo = 1;
		table->philos[0]->isdead = 1;
		return (sem_post(table->dead_sem), 1);
	}
	return (0);
}

int	alive(t_table *table)
{
	int					i;
	unsigned long long	time;

	i = 0;
	while (i < table->num_philo)
	{
		time = real_time();
		sem_wait(table->last_meal_sem);
		if ((time - table->philos[i]->last_meal) > table->death_time)
		{
			sem_post(table->last_meal_sem);
			sem_wait(table->dead_sem);
			table->dead_philo = 1;
			table->philos[i]->isdead = 1;
			sem_post(table->dead_sem);
			sem_wait(table->print_sem);
			printf("[%llu] %d died\n", time - table->start_time, i + 1);
			return (sem_wait(table->print_sem), 1);
		}
		sem_post(table->last_meal_sem);
		i++;
		usleep(50);
	}
	return (0);
}

// void	*monitor(void *arg)
// {
// 	t_table	*table;

// 	table = (t_table *)arg;
// 	while (1)
// 	{
// 		if (alive(table) || eat_count(table))
// 			break ;
// 	}
// 	return (NULL);
// }

int	check_if_dead(t_philo *philo)
{
	int	i;

	i = 1;
	sem_wait(philo->table->dead_sem);
	if (philo->isdead == 0 && philo->table->dead_philo == 0)
		i = 0;
	sem_post(philo->table->dead_sem);
	return (i);
}
