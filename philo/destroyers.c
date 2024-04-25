/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:51:21 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/04/25 12:08:35 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_simulation_mutexes(t_table *table)
{
	pthread_mutex_destroy(&table->simulation);
	pthread_mutex_destroy(&table->printer);
	pthread_mutex_destroy(&table->state_checker);
	pthread_mutex_destroy(&table->life_checker);
}

void	destroy_forks_mutexes(t_table *table, int num_of_forks)
{
	int	i;

	i = 0;
	while (i < num_of_forks)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
}

void	free_simulation_memory(t_table *table)
{
	if (table->philosophers)
		free(table->philosophers);
	if (table->forks)
		free(table->forks);
}

void	clear_simulation(t_table *table)
{
	destroy_forks_mutexes(table, table->num_of_philos);
	destroy_simulation_mutexes(table);
	free_simulation_memory(table);
}
