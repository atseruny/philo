/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:58:50 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/14 20:15:59 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_func(t_philo *philo, int time)
{
	unsigned long long	start;

	start = real_time();
	while (real_time() - start < (unsigned long long)time)
	{
		if (check_if_dead(philo) == 1)
			return ;
		usleep(1000);
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

int	is_hungry(t_philo *philo)
{
	struct timeval	now;
	int				diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - philo->ishungry->tv_sec) * 1000
		+ (now.tv_usec - philo->ishungry->tv_usec) / 1000;
	return (diff);
}

void	start(t_table *table)
{
	int	i;

	i = 0;
	gettimeofday(table->start_time, NULL);
	while (i < table->num_philo)
	{
		gettimeofday(table->philos[i]->ishungry, NULL);
		pthread_create(&table->philos[i]->th, NULL, &life, table->philos[i]);
		i++;
	}
	i = 0;
	is_dead(table);
	while (i < table->num_philo)
		pthread_join(table->philos[i++]->th, NULL);
}
