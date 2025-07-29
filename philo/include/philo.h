/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:22:52 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/29 13:44:25 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_time
{
	size_t			to_die;
	size_t			to_eat;
	size_t			to_sleep;
	size_t			start;
}					t_time;

typedef struct s_philosopher
{
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*active_lock;
	pthread_mutex_t	*meal_lock;
	size_t			last_meal;
	t_time			*time;
	int				id;
	int				meals_eaten;
	int				*active;
	int				meals_needed;
}					t_philosopher;

typedef struct s_simulation
{
	t_philosopher	*philosophers;
	pthread_mutex_t	active_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	int				philosopher_count;
	int				active;
}					t_simulation;

// init.c
t_simulation		*init(int argc, char **argv);

// valid.c
int					is_integer(const char *str);
int					check_arguments(int argc, char **argv);

// utils.c
size_t				get_time(void);
void				precise_sleep(size_t ms);
void				init_mutexes(t_simulation *sim);
int					ft_atoi(const char *str);

// routine.c
void				*routine(void *args);

// monitor.c
int					check_philo_full(t_philosopher *philo);
int					check_philo_dead(t_philosopher *philo, size_t now);
void				handle_philo_death(t_simulation *sim, int i, size_t now);
int					monitor_philo(t_simulation *sim, int i, int *full);
int					monitor_all_philos(t_simulation *sim, int *full);

// cleanup.c
void				*cleanup_on_error(t_simulation *sim, int stage);
void				cleanup_simulation(t_simulation *sim);

// thread.c
void				start_threads(t_simulation *sim);
void				join_threads(t_simulation *sim, pthread_t monitor_thread);

// actions.c
void				philo_think(t_philosopher *philosopher);
void				philo_take_forks(t_philosopher *philosopher);
int					philo_eat(t_philosopher *philosopher);
void				philo_sleep(t_philosopher *philosopher);
