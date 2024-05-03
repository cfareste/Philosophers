/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_helpers_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:58:10 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/05/02 17:07:38 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_time	get_time(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + timestamp.tv_usec / 1000);
}

void	print_state(t_table *table, t_philo *philo, char *state)
{
	t_time	time_now;

	time_now = get_time();
	sem_wait(table->printer);
	printf("[%d] %d %s", time_now - table->simulation_start, philo->num, state);
	sem_post(table->printer);
}

void	kill_philo(t_table *table, t_philo *philo)
{
	t_time	time_now;

	time_now = get_time();
	sem_wait(table->printer);
	printf("[%d] %d %s", time_now - table->simulation_start, philo->num, DIED);
	sem_post(table->deads);
}

void	suspend(t_time time)
{
	t_time	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(100);
}
