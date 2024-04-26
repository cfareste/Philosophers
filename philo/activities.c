/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activities.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chris <chris@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 13:34:55 by chris             #+#    #+#             */
/*   Updated: 2024/04/26 16:43:15 by chris            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	think(t_philo *philo)
{
	print_state(philo->table, philo, THINKING_STATE);
    return (1);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_state(philo->table, philo, TAKEN_FORK_STATE);
	if (philo->right_fork == philo->left_fork)
		return (pthread_mutex_unlock(philo->right_fork), 0);
	pthread_mutex_lock(philo->left_fork);
	print_state(philo->table, philo, TAKEN_FORK_STATE);
	pthread_mutex_lock(&philo->table->state_checker);
	print_state(philo->table, philo, EATING_STATE);
	philo->last_meal = get_time();
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->table->state_checker);
	suspend(philo->table->time_to_eat);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

int	sleep_nap(t_philo *philo)
{
	print_state(philo->table, philo, SLEEPING_STATE);
	suspend(philo->table->time_to_sleep);
	return (1);
}
