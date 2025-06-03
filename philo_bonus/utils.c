/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:09:13 by atseruny          #+#    #+#             */
/*   Updated: 2025/06/03 20:25:41 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void	closing(t_table *table)
{
	sem_close(table->semaphores);
	sem_close(table->dead_sem);
	sem_close(table->meals);
	sem_close(table->curr_meal_sem);
	sem_close(table->last_meal_sem);
	sem_close(table->dead_check);
	sem_close(table->print_sem);
}

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	sem_close(table->semaphores);
	sem_close(table->dead_sem);
	sem_close(table->meals);
	sem_close(table->curr_meal_sem);
	sem_close(table->last_meal_sem);
	sem_close(table->dead_check);
	sem_close(table->print_sem);
	sem_unlink("/forks");
	sem_unlink("/dead");
	sem_unlink("/curr");
	sem_unlink("/meals");
	sem_unlink("/last");
	sem_unlink("/dead_chek");
	sem_unlink("/print");
	while (i < table->num_philo)
		free(table->philos[i++]);
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
