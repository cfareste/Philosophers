/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:44:02 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/05/03 02:07:55 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	check_meals(t_table *table)
{
	int	i;

	sem_wait(table->meals);
	i = 0;
	while (i++ < table->num_of_philos)
		sem_wait(table->meals);
	if (table->stop_simulation)
		return ;
	table->stop_simulation = 1;
	i = 0;
	while (i < table->num_of_philos)
		kill(table->philosophers[i++].process_id, SIGTERM);
	sem_post(table->deads);
}

static void	check_deads(t_table *table)
{
	int	i;

	sem_wait(table->deads);
	if (table->stop_simulation)
		return ;
	table->stop_simulation = 1;
	i = 0;
	while (i < table->num_of_philos)
	{
		sem_post(table->meals);
		kill(table->philosophers[i].process_id, SIGTERM);
		i++;
	}
}

static void	life_routine(t_table *table, t_philo *philo)
{
	int	i;
	int	status;

	philo->last_meal = table->simulation_start;
	if (pthread_create(&philo->supervisor_th, NULL, (void *)supervise, philo))
		exit(1);
	sem_wait(table->simulation);
	sem_post(table->simulation);
	i = 0;
	status = RUNNING;
	while (status != STOPPED)
	{
		status = philo->activities[i](table, philo);
		if (i == NUM_OF_ACTIVITIES - 1)
			i = 0;
		else
			i++;
	}
	suspend(table->time_to_die);
	kill_philo(table, philo);
	exit(1);
}

static void	wait_philosophers(t_table *table)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < table->num_of_philos)
	{
		waitpid(-1, &status, 0);
		if (!WIFSIGNALED(status) || \
			(WIFSIGNALED(status) && WTERMSIG(status) != SIGTERM))
			sem_post(table->deads);
		i++;
	}
	i = 0;
	while (i < table->num_of_philos)
	{
		pthread_join(table->philosophers[i].supervisor_th, NULL);
		i++;
	}
	pthread_join(table->meals_th, NULL);
	pthread_join(table->deads_th, NULL);
}

int	run_simulation(t_table *table)
{
	int		i;

	i = 0;
	if (pthread_create(&table->meals_th, NULL, (void *)check_meals, table) != 0)
		return (handle_error("Error creating threads\n"), 0);
	if (pthread_create(&table->deads_th, NULL, (void *)check_deads, table) != 0)
		return (handle_error("Error creating threads\n"), 0);
	sem_wait(table->simulation);
	table->simulation_start = get_time();
	while (i < table->num_of_philos)
	{
		table->philosophers[i].process_id = fork();
		if (table->philosophers[i].process_id == -1)
			return (handle_error("Error creating processes\n"), 0);
		if (table->philosophers[i].process_id == 0)
			life_routine(table, &table->philosophers[i]);
		i++;
	}
	sem_post(table->simulation);
	sem_post(table->meals);
	wait_philosophers(table);
	return (1);
}
