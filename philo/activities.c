/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:34:55 by chris             #+#    #+#             */
/*   Updated: 2024/04/29 14:58:02 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	think(t_philo *philo)
{
	return (print_state(philo->table, philo, THINKING_STATE));
}

static void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static int	take_forks(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->right_fork);
	status = print_state(philo->table, philo, TAKEN_FORK_STATE);
	if (status == STOPPED || philo->right_fork == philo->left_fork)
		return (pthread_mutex_unlock(philo->right_fork), 0);
	pthread_mutex_lock(philo->left_fork);
	status = print_state(philo->table, philo, TAKEN_FORK_STATE);
	if (status == STOPPED)
		return (unlock_forks(philo), 0);
	return (status);
}

int	eat(t_philo *philo)
{
	if (take_forks(philo) == STOPPED)
		return (0);
	if (print_state(philo->table, philo, EATING_STATE) == STOPPED)
		return (unlock_forks(philo), 0);
	pthread_mutex_lock(philo->philo_checker);
	if (check_simulation_state(philo) == STOPPED)
	{
		pthread_mutex_unlock(philo->philo_checker);
		unlock_forks(philo);
		return (0);
	}
	philo->last_meal = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(philo->philo_checker);
	suspend(philo->table->time_to_eat);
	unlock_forks(philo);
	return (1);
}

int	sleep_nap(t_philo *philo)
{
	int	status;

	status = print_state(philo->table, philo, SLEEPING_STATE);
	if (status == RUNNING)
		suspend(philo->table->time_to_sleep);
	return (status);
}
