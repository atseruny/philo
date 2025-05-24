/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:16:03 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/24 19:06:41 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_philo(t_philo *philo, t_table *table, int i)
{
	philo->index = i + 1;
	philo->table = table;
	philo->curr_meal = 0;
	philo->isdead = 0;
	philo->left = table->forks[i];
	pthread_mutex_init(&philo->curr_meal_mutex, NULL);
	pthread_mutex_init(&philo->last_meal_mutex, NULL);
	philo->right = table->forks[(i + 1) % table->num_philo];
}

void	get_table_sharunak(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		table->philos[i] = malloc(sizeof(t_philo));
		table->forks[i] = malloc(sizeof(pthread_mutex_t));
		if (!table->philos[i] || !table->forks[i])
			return ;
		pthread_mutex_init(table->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < table->num_philo)
	{
		get_philo(table->philos[i], table, i);
		i++;
	}
}

void	get_table(int argc, char **argv, t_table *table)
{
	table->num_philo = ft_atol(argv[1]);
	table->death_time = (unsigned long long)ft_atol(argv[2]);
	table->eat_time = ft_atol(argv[3]);
	table->sleep_time = ft_atol(argv[4]);
	if (argc == 6)
		table->must_eat = ft_atol(argv[5]);
	else
		table->must_eat = -1;
	table->dead_philo = 0;
	table->kusht = 0;
	pthread_mutex_init(&table->dead, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	// pthread_mutex_init(&table->must_mutex, NULL);
	pthread_mutex_init(&table->kusht_mutex, NULL);
	table->philos = malloc(table->num_philo * sizeof(t_philo *));
	table->forks = malloc(table->num_philo * sizeof(pthread_mutex_t *));
	if (!table->philos || !table->forks)
		return ;
	get_table_sharunak(table);
}

int	is_valid(char *s)
{
	int	i;

	i = 0;
	if (*s == '+')
		s++;
	while (s[i] != '\0')
	{
		if (ft_isdigit(s[i]) == 0)
			return (0);
		i++;
	}
	if (ft_atol(s) <= 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	int		i;
	t_table	table;

	i = 1;
	if (argc < 5 || argc > 6)
		return (write(2, "Wrong number of arguments\n", 28), 1);
	while (argv[i] != NULL)
	{
		if (is_valid(argv[i++]) == 0)
			return (write(2, "Invalid input\n", 14), 1);
	}
	get_table(argc, argv, &table);
	start(&table);
	free_all(&table);
	return (0);
}
