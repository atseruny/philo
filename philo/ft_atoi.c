/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:03:30 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/05 18:46:19 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

static int	ft_strtoint(char ch)
{
	int	n;

	n = ch - '0';
	return (n);
}

static long long	ft_num(int len, char *str)
{
	int			i;
	int			n;
	long long	num;

	num = 0;
	i = 0;
	while (i < len && str[i] != '\0')
	{
		n = ft_strtoint(str[i]);
		num = num * 10 + n;
		i++;
	}
	return (num);
}

int	ft_isspace(char s)
{
	if (s == '\t' || s == '\n' || s == '\v'
		|| s == '\f' || s == '\r' || s == ' ')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int			i;
	long long	num;

	num = 0;
	i = 0;
	if ((char)str[i] == '+')
		i++;
	while (str[i] == '0')
		i++;
	str += i;
	i = 0;
	while (str[i] != '\0' && ft_isdigit(str[i]) == 1)
		i++;
	if (str[i] != '\0' || ft_strlen(str) > 11)
		return (-1);
	num = ft_num(i, str);
	if (num > 2147483647 || num < -2147483648)
		return (-1);
	return ((int)num);
}
