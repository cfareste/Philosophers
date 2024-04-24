/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:01:57 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/04/24 19:00:57 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// Checker macros
# define MAX_ARG_LENGTH 11

// Initiators macros
# define NUM_OF_PHILOS_IDX 0
# define TTDIE_IDX 1
# define TTEAT_IDX 2
# define TTSLEEP_IDX 3
# define MEALS_IDX 4

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

// Structures and types
typedef pthread_mutex_t	t_mutex;
typedef int				t_time;
typedef struct s_table	t_table;
typedef struct s_philo	t_philo;

struct s_table
{
	int		all_philos_alive;
	int		num_of_philos;
	int		meals_per_philo;
	t_time	time_to_die;
	t_time	time_to_eat;
	t_time	time_to_sleep;
	t_philo	*philosophers;
	t_mutex	*forks;
	t_mutex	life_checker;
	t_mutex	printer;
	t_mutex	simulation;
};

struct s_philo
{
	pthread_t	thread_id;
	int			num;
	int			times_eaten;
	t_time		last_meal;
	t_mutex		*right_fork;
	t_mutex		*left_fork;
	t_table		*table;
};


// Checker
int		check_args_validity(char **argv);

// Initiators
int		init_simulation(t_table *table, char **argv);

// Destroyers
void	destroy_simulation_mutexes(t_table *table);
void	destroy_forks_mutexes(t_table *table, int num_of_forks);
void	free_simulation_memory(t_table *table);
void	clear_simulation(t_table *table);

// Utils
int		ft_isdigit(int c);
int		ft_strlen(char *str);
long	ft_atol(char *number);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

// Error handler
void	handle_error(char *error);

#endif
