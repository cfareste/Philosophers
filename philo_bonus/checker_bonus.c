/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:15:16 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/05/03 01:05:05 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	is_number(char *argument)
{
	int	i;

	i = 0;
	if (!argument[i])
		return (0);
	if (argument[i] == '-' || argument[i] == '+')
		i++;
	while (argument[i] && argument[i] == '0')
		i++;
	while (argument[i])
	{
		if (!ft_isdigit(argument[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	is_int(char *number)
{
	long	long_num;
	int		num_len;
	int		i;

	i = 0;
	if (number[i] == '-' || number[i] == '+')
		i++;
	while (number[i] && number[i] == '0')
		i++;
	num_len = ft_strlen(&number[i]);
	long_num = ft_atol(number);
	if (num_len > MAX_ARG_LENGTH || long_num < INT_MIN || long_num > INT_MAX)
		return (0);
	return (1);
}

int	check_args_validity(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!is_number(argv[i]) || !is_int(argv[i]) || ft_atol(argv[i]) <= 0)
			return (0);
		i++;
	}
	return (1);
}
