/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:09:13 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/28 17:02:17 by atseruny         ###   ########.fr       */
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

void	*ft_memset(void *str, int c, int len)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = str;
	while (i < len)
	{
		*ptr = c;
		ptr++;
		i++;
	}
	return (str);
}

void	*ft_calloc(int count, int size)
{
	void	*p;
	int		i;

	i = 0;
	if (size * count > 65536)
		return (NULL);
	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_memset(p, 0, count * size);
	return (p);
}
