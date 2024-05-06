/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:01:57 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/05/06 15:27:24 by cfidalgo         ###   ########.fr       */
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

// States macros
# define TAKEN_FORK_STATE "has taken a fork\n"
# define EATING_STATE "is eating\n"
# define SLEEPING_STATE "is sleeping\n"
# define THINKING_STATE "is thinking\n"
# define DIED "died\n"

// Simulation macros
# define RUNNING 1
# define STOPPED 0

// Activities macros
# define NUM_OF_ACTIVITIES 3
# define THINK 0
# define EAT 1
# define SLEEP 2

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
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
	int		stop_simulation;
	int		num_of_philos;
	int		meals_per_philo;
	t_time	time_to_die;
	t_time	time_to_eat;
	t_time	time_to_sleep;
	t_time	simulation_start;
	t_philo	*philosophers;
	t_mutex	*forks;
	t_mutex	life_checker;
	t_mutex	*philo_checkers;
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
	t_mutex		*philo_checker;
	int			(*activities[NUM_OF_ACTIVITIES])(t_philo *philo);
	t_table		*table;
};

// Checker
int		check_args_validity(char **argv);

// Initiators
int		init_simulation(t_table *table, char **argv);

// Destroyers
void	destroy_simulation_mutexes(t_table *table);
void	destroy_forks_mutexes(t_table *table, int num_of_forks);
void	destroy_philo_checkers_mutexes(t_table *table, int num_of_checkers);
void	free_simulation_memory(t_table *table);
void	clear_simulation(t_table *table);

// Simulation
int		check_simulation_state(t_philo *philo);
int		run_simulation(t_table *table);

// Simulation utils
t_time	get_time(void);
int		print_state(t_table *table, t_philo *philo, char *state);
void	kill_philo(t_table *table, t_philo *philo);
void	suspend(t_time time);
int		all_meals_eaten(t_table *table, int num_of_philos_eaten_enough);

// Activities
int		think(t_philo *philo);
int		eat(t_philo *philo);
int		sleep_nap(t_philo *philo);

// Utils
int		ft_isdigit(int c);
int		ft_strlen(char *str);
long	ft_atol(char *number);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

// Error handler
void	handle_error(char *error);

#endif
