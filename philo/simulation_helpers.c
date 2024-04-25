/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:58:10 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/04/25 15:56:04 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	pthread_mutex_lock(&table->printer);
	pthread_mutex_lock(&table->life_checker);
	if (!table->stop_simulation)
	{
		pthread_mutex_unlock(&table->life_checker);
		printf("[%d] %d %s", time_now - table->simulation_start, \
			philo->num, state);
	}
	else
		pthread_mutex_unlock(&table->life_checker);
	pthread_mutex_unlock(&table->printer);
}

void	kill_philo(t_table *table, t_philo *philo)
{
	t_time	time_now;

	time_now = get_time();
	pthread_mutex_lock(&table->life_checker);
	table->stop_simulation = 1;
	pthread_mutex_unlock(&table->life_checker);
	pthread_mutex_lock(&table->printer);
	printf("[%d] %d %s", time_now - table->simulation_start, philo->num, DIED);
	pthread_mutex_unlock(&table->printer);
}

void	suspend(t_time time)
{
	t_time	start_time;

	start_time = get_time();
	while (get_time() - start_time <= time)
		usleep(100);
}

int	all_meals_eaten(t_table *table, int num_of_philos_eaten_enough)
{
	if (table->num_of_philos == num_of_philos_eaten_enough)
	{
		pthread_mutex_lock(&table->life_checker);
		table->stop_simulation = 1;
		pthread_mutex_unlock(&table->life_checker);
		return (1);
	}
	return (0);
}
