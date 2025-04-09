/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidmalasek <davidmalasek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:22:52 by dmalasek          #+#    #+#             */
/*   Updated: 2025/04/09 21:35:35 by davidmalase      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>   // free()
#include <sys/time.h> // gettimeofday()

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
	int				id;
	int				meals_eaten;
}					t_philosopher;

typedef struct s_simulation
{
	t_philosopher	*philosophers;
	pthread_mutex_t	active_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	*forks;
	t_time			*time;
	int				philosopher_count;
	int				active;
	int				meals_needed;
}					t_simulation;

// Init
t_simulation	*init(int argc, char **argv);

// Valid
int					is_integer(const char *str);
int					check_arguments(int argc, char **argv);