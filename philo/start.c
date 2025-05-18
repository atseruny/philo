/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:58:50 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/18 21:07:50 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_dead(t_table *table)
{
	int	i;

	i = 0;
	while (1)
	{
		if (is_hungry(table->philos[i]) > (long long)table->death_time)
		{
			pthread_mutex_lock(table->death);
			table->isdead = 1;
			table->philos[i]->isdead = 1;
			pthread_mutex_unlock(table->death);
			printf("[%lld] %d died\n", real_time() - table->start_time,
				table->philos[i]->index + 1);
			break ;
		}
		if (table->kusht >= table->num_philo)
		{
			pthread_mutex_lock(table->death);
			table->isdead = 1;
			table->philos[i]->isdead = 1;
			pthread_mutex_unlock(table->death);
			printf("[%lld] dinner is over\n", real_time() - table->start_time);
			break ;
		}
		i = (i + 1) % table->num_philo;
	}
}

void	usleep_func(t_philo *philo, int time)
{
	long long	start;

	start = real_time();
	while (real_time() - start < (long long)time)
	{
		if (check_if_dead(philo) == 1)
			return ;
		usleep(1200);
	}
}

void	*life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 1)
		usleep(100);
	while (check_if_dead(philo) == 0)
	{
		if (is_eating(philo) == 0)
			break ;
		if (is_sleeping(philo) == 0)
			break ;
		if (is_thinking(philo) == 0)
			break ;
	}
	return (NULL);
}

long long	is_hungry(t_philo *philo)
{
	long long	diff;

	diff = real_time() - (philo->ishungry);
	return (diff);
}

void	start(t_table *table)
{
	int	i;

	i = 0;
	table->start_time = real_time();
	while (i < table->num_philo)
	{
		table->philos[i]->ishungry = real_time();
		pthread_create(&table->philos[i]->th, NULL, &life, table->philos[i]);
		i++;
	}
	i = 0;
	is_dead(table);
	while (i < table->num_philo)
		pthread_join(table->philos[i++]->th, NULL);
}
