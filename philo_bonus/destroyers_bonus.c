/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroyers_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:51:21 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/05/06 13:04:02 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	close_semaphores(t_table *table)
{
	sem_close(table->forks);
	sem_close(table->life_checker);
	sem_close(table->printer);
	sem_close(table->simulation);
	sem_close(table->deads);
	sem_close(table->meals);
}

void	unlink_semaphores(void)
{
	sem_unlink("/forks");
	sem_unlink("/life_checker");
	sem_unlink("/printer");
	sem_unlink("/simulation");
	sem_unlink("/deads");
	sem_unlink("/meals");
}

void	destroy_mutexes(t_table *table)
{
	pthread_mutex_destroy(&table->pid_mutex);
	pthread_mutex_destroy(&table->simulation_checker);
}

void	free_simulation_memory(t_table *table)
{
	if (table->philosophers)
		free(table->philosophers);
}

void	clear_simulation(t_table *table)
{
	close_semaphores(table);
	unlink_semaphores();
	destroy_mutexes(table);
	free_simulation_memory(table);
}
