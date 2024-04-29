/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiators.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:57:25 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/04/29 15:38:00 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		table->philosophers[i].num = i + 1;
		table->philosophers[i].times_eaten = 0;
		table->philosophers[i].right_fork = &table->forks[i];
		if (i != table->num_of_philos - 1)
			table->philosophers[i].left_fork = &table->forks[i + 1];
		else
			table->philosophers[i].left_fork = &table->forks[0];
		table->philosophers[i].activities[THINK] = think;
		table->philosophers[i].activities[EAT] = eat;
		table->philosophers[i].activities[SLEEP] = sleep_nap;
		table->philosophers[i].philo_checker = &table->philo_checkers[i];
		table->philosophers[i].table = table;
		i++;
	}
}

static int	init_philo_checkers(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->philo_checkers[i], NULL) != 0)
		{
			destroy_simulation_mutexes(table);
			destroy_philo_checkers_mutexes(table, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
		{
			destroy_simulation_mutexes(table);
			destroy_philo_checkers_mutexes(table, table->num_of_philos);
			destroy_forks_mutexes(table, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	init_mutexes(t_table *table)
{
	if (pthread_mutex_init(&table->simulation, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&table->printer, NULL) != 0)
		return (pthread_mutex_destroy(&table->simulation), 0);
	if (pthread_mutex_init(&table->life_checker, NULL) != 0)
	{
		pthread_mutex_destroy(&table->simulation);
		pthread_mutex_destroy(&table->printer);
		return (0);
	}
	if (!init_philo_checkers(table))
		return (0);
	if (!init_forks(table))
		return (0);
	return (1);
}

int	init_simulation(t_table *table, char **argv)
{
	ft_bzero(table, sizeof(t_table));
	table->num_of_philos = ft_atol(argv[NUM_OF_PHILOS_IDX]);
	table->time_to_die = ft_atol(argv[TTDIE_IDX]);
	table->time_to_eat = ft_atol(argv[TTEAT_IDX]);
	table->time_to_sleep = ft_atol(argv[TTSLEEP_IDX]);
	table->meals_per_philo = -1;
	if (argv[MEALS_IDX])
		table->meals_per_philo = ft_atol(argv[MEALS_IDX]);
	if (!table->num_of_philos || (argv[MEALS_IDX] && !table->meals_per_philo))
		return (0);
	table->philosophers = ft_calloc(table->num_of_philos, sizeof(t_philo));
	if (!table->philosophers)
		return (handle_error("Error allocating memory\n"), 0);
	table->forks = ft_calloc(table->num_of_philos, sizeof(t_mutex));
	if (!table->forks)
		return (handle_error("Error allocating memory\n"), 0);
	table->philo_checkers = ft_calloc(table->num_of_philos, sizeof(t_mutex));
	if (!table->philo_checkers)
		return (handle_error("Error allocating memory\n"), 0);
	if (!init_mutexes(table))
		return (handle_error("Error initializing mutexes\n"), 0);
	init_philos(table);
	return (1);
}
