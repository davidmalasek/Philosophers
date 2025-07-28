/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:22:52 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/28 18:17:56 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>   // free()
#include <sys/time.h> // gettimeofday()
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

// routine.c
void				*routine(void *args);