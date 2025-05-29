/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 17:27:51 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/29 20:51:16 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
	sem_wait(philo->table->print_sem);
	if (check_if_dead(philo))
	{
		sem_post(philo->table->print_sem);
		return ;
	}
	printf("[%llu] %d %s", real_time() - philo->table->start_time,
		philo->index, mess);
	sem_post(philo->table->print_sem);
}

void	life(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->index % 2 == 0)
		usleep_func(philo, philo->table->eat_time - 10);
	while (!check_if_dead(philo))
	{
		if (!eating(philo))
			break;
		if (!sleeping(philo))
			break;
		if (!thinking(philo))
			break;
	}
	exit (0);
}

void	start(t_table *table)
{
	int		i;

	i = 0;
	table->start_time = real_time();
	while (i < table->num_philo)
	{
		table->philos[i]->last_meal = table->start_time;
		table->philos[i]->pid = fork();
		if (table->philos[i]->pid == 0)
			life(table->philos[i]);
		else
			i++;
	}

	//in philos process create 2 threads the life and the monitoring


	i = 0;
	while (i < table->num_philo)
		waitpid(table->philos[i++]->pid, NULL, 0);

}

unsigned long long	real_time(void)
{
	struct timeval		now;

	gettimeofday(&now, NULL);
	return (now.tv_sec * 1000 + now.tv_usec / 1000);
}
