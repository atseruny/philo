/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:34:20 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/14 20:18:04 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	free(table->start_time);
	pthread_mutex_destroy(table->death);
	free(table->death);
	while (i < table->num_philo)
	{
		free(table->philos[i]->ishungry);
		pthread_mutex_destroy(table->forks[i]);
		free(table->forks[i]);
		free(table->philos[i]);
		i++;
	}
	free(table->forks);
	free(table->philos);
}

int	check_if_dead(t_philo *philo)
{
	int	death;

	pthread_mutex_lock(philo->table->death);
	if (philo->isdead == 0 && philo->table->isdead == 0)
		death = 0;
	else
		death = 1;
	pthread_mutex_unlock(philo->table->death);
	return (death);
}

unsigned long long	get_time(t_philo *philo)
{
	struct timeval		now;
	unsigned long long	diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - philo->table->start_time->tv_sec) * 1000
		+ (now.tv_usec - philo->table->start_time->tv_usec) / 1000;
	return (diff);
}

unsigned long long	real_time(void)
{
	struct timeval		now;
	unsigned long long	time;

	gettimeofday(&now, NULL);
	time = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (time);
}
