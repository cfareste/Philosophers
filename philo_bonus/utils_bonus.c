/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:16:07 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/05/02 10:37:49 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atol(char *number)
{
	long	long_num;
	int		neg;
	int		i;

	i = 0;
	neg = 1;
	long_num = 0;
	if (number[i] == '-' || number[i] == '+')
		if (number[i++] == '-')
			neg = -1;
	while (number[i])
		long_num = long_num * 10 + (number[i++] - '0');
	long_num *= neg;
	return (long_num);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*char_s;

	i = 0;
	char_s = s;
	while (i < n)
	{
		char_s[i] = 0;
		i++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (ptr)
		ft_bzero(ptr, size * count);
	return (ptr);
}
