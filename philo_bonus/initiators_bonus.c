/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiators_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:57:25 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/05/03 00:26:02 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_of_philos)
	{
		table->philosophers[i].num = i + 1;
		table->philosophers[i].times_eaten = 0;
		table->philosophers[i].activities[THINK] = think;
		table->philosophers[i].activities[EAT] = eat;
		table->philosophers[i].activities[SLEEP] = sleep_nap;
		table->philosophers[i].table = table;
		i++;
	}
}

static int	open_thread_semaphores(t_table *table)
{
	table->deads = sem_open("/deads", O_CREAT, SEM_MODE, 0);
	if (table->deads == SEM_FAILED)
	{
		sem_close(table->forks);
		sem_close(table->life_checker);
		sem_close(table->printer);
		sem_close(table->simulation);
		return (0);
	}
	table->meals = sem_open("/meals", O_CREAT, SEM_MODE, 0);
	if (table->deads == SEM_FAILED)
	{
		sem_close(table->forks);
		sem_close(table->life_checker);
		sem_close(table->printer);
		sem_close(table->simulation);
		sem_close(table->deads);
		return (0);
	}
	return (1);
}

static int	open_semaphores(t_table *table)
{
	unlink_semaphores();
	table->forks = sem_open("/forks", O_CREAT, SEM_MODE, table->num_of_philos);
	if (table->forks == SEM_FAILED)
		return (0);
	table->life_checker = sem_open("/life_checker", O_CREAT, SEM_MODE, 1);
	if (table->life_checker == SEM_FAILED)
		return (sem_close(table->forks), sem_unlink("/forks"), 0);
	table->printer = sem_open("/printer", O_CREAT, SEM_MODE, 1);
	if (table->printer == SEM_FAILED)
	{
		sem_close(table->forks);
		sem_close(table->life_checker);
		return (unlink_semaphores(), 0);
	}
	table->simulation = sem_open("/simulation", O_CREAT, SEM_MODE, 1);
	if (table->simulation == SEM_FAILED)
	{
		sem_close(table->forks);
		sem_close(table->life_checker);
		sem_close(table->printer);
		return (unlink_semaphores(), 0);
	}
	if (!open_thread_semaphores(table))
		return (unlink_semaphores(), 0);
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
	if (!open_semaphores(table))
		return (handle_error("Error opening semaphores\n"), 0);
	init_philos(table);
	return (1);
}
