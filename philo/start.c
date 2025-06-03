/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:27:51 by atseruny          #+#    #+#             */
/*   Updated: 2025/06/03 17:45:15 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	usleep_func(t_philo *philo, int time)
{
	unsigned long long	start;

	start = real_time();
	while (real_time() - start < (unsigned long long)time)
	{
		if (check_if_dead(philo))
			return ;
		usleep(100);
	}
}

void	print_mess(t_philo *philo, char *mess)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (check_if_dead(philo))
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return ;
	}
	printf("[%llu] %d %s", real_time() - philo->table->start_time,
		philo->index, mess);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	*life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		usleep_func(philo, philo->table->eat_time - 10);
	while (!check_if_dead(philo))
	{
		if (!eating(philo))
			break ;
		if (!sleeping(philo))
			break ;
		if (!thinking(philo))
			break ;
	}
	return (NULL);
}

void	start(t_table *table)
{
	int			i;
	pthread_t	death;

	i = 0;
	table->start_time = real_time();
	while (i < table->num_philo)
	{
		pthread_mutex_lock(&table->philos[i]->last_meal_mutex);
		table->philos[i]->last_meal = table->start_time;
		pthread_mutex_unlock(&table->philos[i]->last_meal_mutex);
		pthread_create(&table->philos[i]->th, NULL, &life, table->philos[i]);
		i++;
	}
	usleep(50);
	pthread_create(&death, NULL, &monitor, table);
	i = 0;
	while (i < table->num_philo)
		pthread_join(table->philos[i++]->th, NULL);
	pthread_join(death, NULL);
}

unsigned long long	real_time(void)
{
	struct timeval		now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}
