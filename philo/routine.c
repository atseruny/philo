/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:56:12 by atseruny          #+#    #+#             */
/*   Updated: 2025/06/03 17:44:50 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat_count(t_table *table)
{
	int	k;
	int	i;

	k = 0;
	i = 0;
	while (i < table->num_philo)
	{
		pthread_mutex_lock(&table->philos[i]->curr_meal_mutex);
		if (table->must_eat != -1
			&& table->philos[i]->curr_meal >= table->must_eat)
			k++;
		pthread_mutex_unlock(&table->philos[i]->curr_meal_mutex);
		i++;
		usleep(50);
	}
	if (k == table->num_philo)
	{
		pthread_mutex_lock(&table->dead);
		table->dead_philo = 1;
		table->philos[0]->isdead = 1;
		return (pthread_mutex_unlock(&table->dead), 1);
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
		pthread_mutex_lock(&table->philos[i]->last_meal_mutex);
		if ((time - table->philos[i]->last_meal) > table->death_time)
		{
			pthread_mutex_unlock(&table->philos[i]->last_meal_mutex);
			pthread_mutex_lock(&table->dead);
			table->dead_philo = 1;
			table->philos[i]->isdead = 1;
			pthread_mutex_unlock(&table->dead);
			pthread_mutex_lock(&table->print_mutex);
			printf("[%llu] %d died\n", time - table->start_time, i + 1);
			return (pthread_mutex_unlock(&table->print_mutex), 1);
		}
		pthread_mutex_unlock(&table->philos[i]->last_meal_mutex);
		i++;
		usleep(50);
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	while (1)
	{
		if (alive(table) || eat_count(table))
			break ;
	}
	return (NULL);
}

int	check_if_dead(t_philo *philo)
{
	int	i;

	i = 1;
	pthread_mutex_lock(&philo->table->dead);
	if (philo->isdead == 0 && philo->table->dead_philo == 0)
		i = 0;
	pthread_mutex_unlock(&philo->table->dead);
	return (i);
}
