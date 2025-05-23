/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:09:13 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/23 19:29:18 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strlen(char *str)
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
	pthread_mutex_destroy(&table->dead);
	pthread_mutex_destroy(&table->kusht_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->philos[i]->curr_meal_mutex);
		pthread_mutex_destroy(&table->philos[i]->last_meal_mutex);
		pthread_mutex_destroy(table->forks[i]);

		free(table->forks[i]);
		free(table->philos[i]);
		i++;
	}
	free(table->forks);
	free(table->philos);
}
