/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:27:51 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/24 19:57:55 by atseruny         ###   ########.fr       */
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
		usleep(50);
	}
}

void	print_mess(t_philo *philo, char *mess)
{
	pthread_mutex_lock(&philo->table->print_mutex);
	if (check_if_dead(philo) == 1)
	{
		pthread_mutex_unlock(&philo->table->print_mutex);
		return ;
	}
	pthread_mutex_lock(&philo->table->kusht_mutex);
	if (philo->table->kusht >= philo->table->num_philo)
	{
		pthread_mutex_unlock(&philo->table->kusht_mutex);
		pthread_mutex_unlock(&philo->table->print_mutex);
		return ;
	}
	pthread_mutex_unlock(&philo->table->kusht_mutex);
	printf("[%llu] %d %s", real_time() - philo->table->start_time,
		philo->index, mess);
	pthread_mutex_unlock(&philo->table->print_mutex);
}

void	*life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		usleep(1000);
	while (check_if_dead(philo) == 0)
	{
		if (eating(philo) == 0)
			break;
		if (sleeping(philo) == 0)
			break;
		if (thinking(philo) == 0)
			break;
	}
	pthread_mutex_unlock(&philo->table->print_mutex);
	return (NULL);
}

void	start(t_table *table)
{
	int			i;
	pthread_t	death;
	// pthread_t	eat;

	i = 0;
	table->start_time = real_time();
	while (i < table->num_philo)
	{
		pthread_create(&table->philos[i]->th, NULL, &life, table->philos[i]);
		pthread_mutex_lock(&table->philos[i]->last_meal_mutex);
		table->philos[i]->last_meal = real_time();
		pthread_mutex_unlock(&table->philos[i++]->last_meal_mutex);
	}
	
	usleep(200);
	pthread_create(&death, NULL, &alive, table);
	// if (table->must_eat != -1)
	// 	pthread_create(&eat, NULL, &eat_count, table);
	// pthread_mutex_unlock(&table->print_mutex);
	// if (table->must_eat != -1)
	// 	pthread_join(eat, NULL);
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
