/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 18:42:10 by atseruny          #+#    #+#             */
/*   Updated: 2025/05/26 17:21:52 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, count * size);
	return (p);
}
