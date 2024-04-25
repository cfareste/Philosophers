/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:44:02 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/04/25 18:29:18 by cfidalgo         ###   ########.fr       */
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

static int	eat_meal(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state(philo->table, philo, TAKEN_FORK);
	if (philo->right_fork == philo->left_fork)
		return (pthread_mutex_unlock(philo->right_fork), 0);
	pthread_mutex_lock(philo->left_fork);
	print_state(philo->table, philo, TAKEN_FORK);
	pthread_mutex_lock(&philo->table->state_checker);
	print_state(philo->table, philo, EATING);
	philo->last_meal = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->table->state_checker);
	suspend(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

static void	*life_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->simulation);
	pthread_mutex_unlock(&philo->table->simulation);
	if (!(philo->num & 1))
	{
		print_state(philo->table, philo, SLEEPING);
		suspend(philo->table->time_to_sleep);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->table->life_checker);
		if (philo->table->stop_simulation)
		{
			pthread_mutex_unlock(&philo->table->life_checker);
			break ;
		}
		pthread_mutex_unlock(&philo->table->life_checker);
		print_state(philo->table, philo, THINKING);
		if (!eat_meal(philo))
			break ;
		print_state(philo->table, philo, SLEEPING);
		suspend(philo->table->time_to_sleep);
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
