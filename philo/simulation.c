/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:44:02 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/04/26 16:25:27 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	supervise_simulation(t_table *table)
{
	int	i;
	int	num_of_philos_eaten_enough;

	i = 0;
	num_of_philos_eaten_enough = 0;
	while (!table->stop_simulation)
	{
		if (i == table->num_of_philos)
		{
			i = 0;
			num_of_philos_eaten_enough = 0;
		}
		pthread_mutex_lock(&table->state_checker);
		if (table->meals_per_philo <= table->philosophers[i].times_eaten
			&& table->meals_per_philo != -1)
			num_of_philos_eaten_enough++;
		pthread_mutex_unlock(&table->state_checker);
		if (all_meals_eaten(table, num_of_philos_eaten_enough))
			break ;
		pthread_mutex_lock(&table->state_checker);
		if (get_time() - table->philosophers[i].last_meal >= table->time_to_die)
			kill_philo(table, &table->philosophers[i]);
		pthread_mutex_unlock(&table->state_checker);
		i++;
	}
}

static int	check_simulation_state(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->life_checker);
	if (philo->table->stop_simulation)
	{
		pthread_mutex_unlock(&philo->table->life_checker);
		return (0);
	}
	pthread_mutex_unlock(&philo->table->life_checker);
	return (1);
}

static void	*life_routine(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->table->simulation);
	pthread_mutex_unlock(&philo->table->simulation);
	i = THINK;
	if (!(philo->num & 1))
		i = SLEEP;
	while (SIMULATION_IS_RUNNING)
	{
		if (i == THINK && !check_simulation_state(philo))
			break ;
		if (!philo->activities[i](philo))
			break ;
		if (i == SLEEP)
			i = THINK;
		else
			i++;
	}
	return (NULL);
}

int	run_simulation(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&table->simulation);
	while (i < table->num_of_philos)
	{
		if (pthread_create(&table->philosophers[i].thread_id, NULL, \
			(void *) life_routine, &table->philosophers[i]) != 0)
			return (handle_error("Error creating threads\n"), 0);
		i++;
	}
	table->simulation_start = get_time();
	i = 0;
	while (i < table->num_of_philos)
		table->philosophers[i++].last_meal = table->simulation_start;
	pthread_mutex_unlock(&table->simulation);
	supervise_simulation(table);
	i = 0;
	while (i < table->num_of_philos)
		pthread_join(table->philosophers[i++].thread_id, NULL);
	return (1);
}
