/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfidalgo <cfidalgo@student.42barcelona.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:01:57 by cfidalgo          #+#    #+#             */
/*   Updated: 2024/05/03 01:27:27 by cfidalgo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

// Checker macros
# define MAX_ARG_LENGTH 11

// Initiators macros
# define NUM_OF_PHILOS_IDX 0
# define TTDIE_IDX 1
# define TTEAT_IDX 2
# define TTSLEEP_IDX 3
# define MEALS_IDX 4
# define SEM_MODE 600

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
# include <string.h>
# include <signal.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

// Structures and types
typedef pthread_t		t_pth;
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
	t_pth	meals_th;
	t_pth	deads_th;
	sem_t	*forks;
	sem_t	*life_checker;
	sem_t	*printer;
	sem_t	*simulation;
	sem_t	*deads;
	sem_t	*meals;
};

struct s_philo
{
	pid_t	process_id;
	t_pth	supervisor_th;
	int		num;
	int		times_eaten;
	t_time	last_meal;
	t_table	*table;
	int		(*activities[NUM_OF_ACTIVITIES])(t_table *table, t_philo *philo);
};

// Checker
int		check_args_validity(char **argv);

// Initiators
int		init_simulation(t_table *table, char **argv);

// Destroyers
void	destroy_mutexes(t_table *table, int num_of_mutexes);
void	close_semaphores(t_table *table);
void	unlink_semaphores(void);
void	free_simulation_memory(t_table *table);
void	clear_simulation(t_table *table);

// Simulation
int		run_simulation(t_table *table);

// Simulation utils
t_time	get_time(void);
void	print_state(t_table *table, t_philo *philo, char *state);
void	kill_philo(t_table *table, t_philo *philo);
void	suspend(t_time time);
int		all_meals_eaten(t_table *table, int num_of_philos_eaten_enough);

// Activities
void	*supervise(t_philo *philo);
int		think(t_table *table, t_philo *philo);
int		eat(t_table *table, t_philo *philo);
int		sleep_nap(t_table *table, t_philo *philo);

// Utils
int		ft_isdigit(int c);
int		ft_strlen(char *str);
long	ft_atol(char *number);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

// Error handler
void	handle_error(char *error);

#endif
