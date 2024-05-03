/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:46:44 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/05/02 10:37:48 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
		return (handle_error("Incorrect number of arguments\n"), 1);
	if (!check_args_validity(&argv[1]))
		return (handle_error("Invalid arguments\n"), 1);
	if (!init_simulation(&table, &argv[1]))
		return (free_simulation_memory(&table), 1);
	if (!run_simulation(&table))
		return (clear_simulation(&table), 1);
	clear_simulation(&table);
	return (0);
}
