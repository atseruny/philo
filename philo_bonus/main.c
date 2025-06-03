/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 16:16:03 by atseruny          #+#    #+#             */
/*   Updated: 2025/06/03 20:32:49 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	get_table_sharunak(t_table *table)
{
	int	i;

	i = 0;
	table->dead_check = sem_open("/dead_check", O_CREAT | O_EXCL, 0644, 1);
	table->curr_meal_sem = sem_open("/curr", O_CREAT | O_EXCL, 0644, 1);
	table->last_meal_sem = sem_open("/last", O_CREAT | O_EXCL, 0644, 1);
	if (table->semaphores == SEM_FAILED || table->meals == SEM_FAILED
		|| table->dead_sem == SEM_FAILED || table->print_sem == SEM_FAILED
		|| table->last_meal_sem == SEM_FAILED
		|| table->curr_meal_sem == SEM_FAILED)
		exit(1);
	while (i < table->num_philo)
	{
		table->philos[i] = ft_calloc(1, sizeof(t_philo));
		if (!table->philos[i])
			return ;
		table->philos[i]->index = i + 1;
		table->philos[i]->table = table;
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
	table->philos = ft_calloc(table->num_philo, sizeof(t_philo *));
	if (!table->philos)
		return ;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/dead");
	sem_unlink("/dead_check");
	sem_unlink("/last");
	sem_unlink("/curr");
	sem_unlink("/meals");
	table->semaphores = sem_open("/forks", O_CREAT | O_EXCL,
			0644, table->num_philo);
	table->print_sem = sem_open("/print", O_CREAT | O_EXCL, 0644, 1);
	table->dead_sem = sem_open("/dead", O_CREAT | O_EXCL, 0644, 0);
	table->meals = sem_open("/meals", O_CREAT | O_EXCL, 0644, 0);
	get_table_sharunak(table);
}

int	is_valid(char *s)
{
	int	i;

	i = 0;
	if (*s == '+')
		s++;
	while (s[i] != '\0')
		if (!ft_isdigit(s[i++]))
			return (0);
	if (ft_atol(s) <= 0)
		return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	int		i;
	t_table	table;

	i = 2;
	if (argc < 5 || argc > 6)
		return (write(2, "Wrong number of arguments\n", 26), 1);
	if (is_valid(argv[1]) && ft_atol(argv[1]) > 200)
		return (write(2, "Invalid input\n", 14), 1);
	while (argv[i] != NULL)
		if (!is_valid(argv[i++]))
			return (write(2, "Invalid input\n", 14), 1);
	get_table(argc, argv, &table);
	start(&table);
	sem_post(table.print_sem);
	free_all(&table);
	return (0);
}
