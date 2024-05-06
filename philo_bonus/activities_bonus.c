/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:34:55 by chris             #+#    #+#             */
/*   Updated: 2024/05/06 13:30:39 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*supervise(t_philo *philo)
{
	while (RUNNING)
	{
		sem_wait(philo->table->life_checker);
		if (get_time() - philo->last_meal >= philo->table->time_to_die)
		{
			kill_philo(philo->table, philo);
			break ;
		}
		sem_post(philo->table->life_checker);
	}
	return (NULL);
}

int	think(t_table *table, t_philo *philo)
{
	print_state(table, philo, THINKING_STATE);
	return (1);
}

static int	take_forks(t_table *table, t_philo *philo)
{
	sem_wait(table->forks);
	print_state(table, philo, TAKEN_FORK_STATE);
	if (table->num_of_philos == 1)
		return (sem_post(table->forks), 0);
	sem_wait(table->forks);
	print_state(table, philo, TAKEN_FORK_STATE);
	return (1);
}

int	eat(t_table *table, t_philo *philo)
{
	if (take_forks(table, philo) == STOPPED)
		return (0);
	print_state(table, philo, EATING_STATE);
	sem_wait(table->life_checker);
	philo->last_meal = get_time();
	philo->times_eaten++;
	sem_post(table->life_checker);
	suspend(table->time_to_eat);
	sem_post(table->forks);
	sem_post(table->forks);
	if (table->meals_per_philo == philo->times_eaten)
		sem_post(table->meals);
	return (1);
}

int	sleep_nap(t_table *table, t_philo *philo)
{
	print_state(table, philo, SLEEPING_STATE);
	suspend(table->time_to_sleep);
	return (1);
}
