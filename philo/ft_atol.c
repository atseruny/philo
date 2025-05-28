/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 15:03:30 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/28 16:53:56 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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

int	ft_atol(char *str)
{
	int			i;
	long long	num;

	num = 0;
	i = 0;
	while (*str == '0')
		str++;
	while (str[i] != '\0' && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0' || ft_strlen(str) > 11)
		return (-1);
	num = ft_num(i, str);
	if (num > 2147483647)
		return (-1);
	return ((int)num);
}
