/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:34:20 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/18 19:49:14 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(table->death);
	free(table->death);
	while (i < table->num_philo)
	{
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

long long	real_time(void)
{
	struct timeval		now;
	unsigned long long	time;

	gettimeofday(&now, NULL);
	time = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (time);
}
