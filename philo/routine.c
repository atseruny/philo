/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:56:12 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/26 20:03:12 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->dead);
	philo->table->dead_philo = 1;
	philo->isdead = 1;
	pthread_mutex_unlock(&philo->table->dead);
}

void	*eat_count(void *arg)
{
	int		i;
	t_table	*table;
	int		k;

	table = (t_table *)arg;
	k = 0;
	i = 0;
	while (1)
	{
		pthread_mutex_lock(&table->philos[i]->curr_meal_mutex);
		if (table->philos[i]->curr_meal == table->must_eat)
			k++;
		pthread_mutex_unlock(&table->philos[i]->curr_meal_mutex);
		if (i == table->num_philo - 1)
		{
			if (k == table->num_philo)
			{
				pthread_mutex_lock(&table->dead);
				table->dead_philo = 1;
				table->philos[i - 1]->isdead = 1;
				return (pthread_mutex_unlock(&table->dead), NULL);
			}
			else
				k = 0;
		}
		if (check_if_dead(table->philos[i]) == 1)
			return (NULL);
		usleep(50);
		i = (i + 1) % table->num_philo;
	}
	return (NULL);
}


void	*alive(void *arg)
{
	int		i;
	int		k;
	t_table	*table;

	table = (t_table *)arg;
	i = 0;
	k = 0;
	while (1)
	{
		pthread_mutex_lock(&table->philos[i]->last_meal_mutex);
		if ((real_time() - table->philos[i]->last_meal) > table->death_time)
		{
			pthread_mutex_unlock(&table->philos[i]->last_meal_mutex);
			pthread_mutex_lock(&table->dead);
			table->dead_philo = 1;
			table->philos[i]->isdead = 1;
			pthread_mutex_unlock(&table->dead);
			pthread_mutex_lock(&table->print_mutex);
			printf("[%llu] %d died\n", real_time() - table->start_time, i + 1);
			return (pthread_mutex_unlock(&table->print_mutex), NULL);
		}
		pthread_mutex_unlock(&table->philos[i]->last_meal_mutex);
		if (check_if_dead(table->philos[i]) == 1)
			return (NULL);
		usleep(50);
		i = (i + 1) % table->num_philo;
	}
	return (NULL);
}

int	check_if_dead(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->table->dead);
	if (philo->isdead == 0 && philo->table->dead_philo == 0)
		i = 0;
	else
		i = 1;
	pthread_mutex_unlock(&philo->table->dead);
	return (i);
}
