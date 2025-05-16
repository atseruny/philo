/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anush <anush@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 20:27:39 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/16 11:25:41 by anush            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	is_valid(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0 && s[i] != '+')
			return (0);
		i++;
	}
	if (ft_atoi(s) == -1)
		return (0);
	return (1);
}

void	get_philo(t_philo *philo, t_table *table, int i)
{
	philo->index = i;
	philo->th = 0;
	philo->isdead = 0;
	philo->curr_meal = 0;
	philo->left = table->forks[i];
	philo->table = table;
	philo->right = table->forks[(i + 1) % table->num_philo];
}

void	get_table(int argc, char **argv, t_table *table)
{
	int		i;

	i = 0;
	table->num_philo = ft_atoi(argv[1]);
	table->death_time = ft_atoi(argv[2]);
	table->eat_time = ft_atoi(argv[3]);
	table->isdead = 0;
	table->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	table->start_time = malloc(sizeof(struct timeval));
	table->philos = malloc(table->num_philo * sizeof(t_philo *));
	table->forks = malloc(table->num_philo * sizeof(pthread_mutex_t *));
	table->death = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(table->death, NULL);
	if (!table->start_time || !table->philos || !table->forks)
		return ;
	while (i < table->num_philo)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		table->forks[i] = malloc(sizeof(pthread_mutex_t));
		table->philos[i]->ishungry = malloc(sizeof(struct timeval));
		if (!table->philos[i] || !table->forks[i] || !table->philos[i]->ishungry)
			return ;
		pthread_mutex_init(table->forks[i], NULL);
		get_philo((table->philos)[i], table, i);
		i++;
	}
	i = 0;
	while (i < table->num_philo)
	{
		get_philo(table->philos[i], table, i);
		i++;
	}
}

int main(int argc, char **argv)
{
	int		i;
	t_table	table;

	if (argc < 5 || argc > 6)
		return (1);
	i = 1;
	while (argv[i] != NULL)
	{
		if (is_valid(argv[i]) == 0)
			return (1);
		i++;
	}
	get_table(argc, argv, &table);
	start(&table);
	free_all(&table);
	return (0);
}
