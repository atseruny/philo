/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:58:50 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/12 16:01:39 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	get_time(t_philo *philo)
{
	struct timeval		now;
	unsigned long long	diff;

	gettimeofday(&now, NULL);
	diff = (now.tv_sec - philo->table->start_time->tv_sec) * 1000 +
	(now.tv_usec - philo->table->start_time->tv_usec) / 1000;
	return diff;
}

void	usleep_func(t_philo *philo, int time)
{
	if (philo->isdead == 1 || philo->table->isdead == 1)
		return ;
	usleep(time);
}

void	*life(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	if (philo->index % 2 == 1)
		usleep(1000);
	while (philo->table->isdead == 0 && philo->isdead == 0)
	{
		if (is_eating(philo) == 0)
			break;
		if (is_sleeping(philo) == 0)
			break;
		if (is_thinking(philo) == 0)
			break;
	}
	return NULL;
}


int	is_hungry(t_philo *philo)
{
	struct timeval	now;
	int		diff;
	
	gettimeofday(&now, NULL);
	diff = (now.tv_sec - philo->ishungry->tv_sec) * 1000 + 
	(now.tv_usec - philo->ishungry->tv_usec) / 1000;
	return diff;
}


void	start(t_table *table)
{
	int	i;
	
	i = 0;
	gettimeofday(table->start_time, NULL);
	while (i < table->num_philo)
	{
		gettimeofday(table->philos[i]->ishungry, NULL);
		pthread_create(&table->philos[i]->th, NULL, &life, table->philos[i]);
		i++;
	}
	i = 0;
	is_dead(table);
	while (i < table->num_philo)
		pthread_join(table->philos[i++]->th, NULL);
}


// void	*life(void *arg)
// {
// 	t_philo *philo;

// 	philo = (t_philo *)arg;
// 	if (philo->index % 2 == 1)
// 		usleep_func(philo, 60);
// 	while (philo->isdead != 1)
// 	{
// 		pthread_mutex_lock(philo->left);
// 		printf("[%llu] %d took left fork\n", get_time(philo), philo->index + 1);
// 		pthread_mutex_lock(philo->right);
// 		printf("[%llu] %d took right fork\n", get_time(philo), philo->index + 1);
// 		printf("[%llu] %d is eating\n", get_time(philo), philo->index + 1);
// 		philo->curr_meal++;
// 		gettimeofday(philo->ishungry, NULL);
// 		usleep_func(philo, philo->table->eat_time * 1000);
// 		pthread_mutex_unlock(philo->right);
// 		pthread_mutex_unlock(philo->left);
// 		printf("[%llu] %d is sleeping\n", get_time(philo), philo->index + 1);
// 		usleep_func(philo, philo->table->sleep_time);
// 		printf("[%llu] %d is thinking\n", get_time(philo), philo->index + 1);
// 	}
// }













// int mails=0;
// int prime[5] = {2, 3, 5, 7, 11};

// void *route(void *arg)
// {
// 	int i = *(int *)arg;
// 	printf("%d\n", prime[i]);
// }

// int main()
// {
// 	pthread_t th[5];
// 	time_t t;
// 	t=time(NULL);
// 	printf("Time is: %ld", t);
// 	pthread_mutex_t mutex;
// 	pthread_mutex_init(&mutex, NULL);
// 	for (int i = 0; i < 5; i++)
// 	{
// 		if (pthread_create(th + i, NULL, &route, &i) != 0)
// 			return 1;
// 	}
// 	for (int i = 0; i < 5; i++)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			return 1;
// 	}
// 	pthread_mutex_destroy(&mutex);

// }