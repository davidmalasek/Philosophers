/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:22:52 by dmalasek          #+#    #+#             */
/*   Updated: 2025/03/02 16:51:19 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h> // gettimeofday()

typedef struct s_time
{
	size_t			last_meal;
	size_t			to_die;
	size_t			to_eat;
	size_t			to_sleep;
}					t_time;

typedef struct s_philosopher
{
	pthread_t		thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_time			*time;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	int				id;
	int				meals_eaten;
}					t_philosopher;

typedef struct s_simulation
{
	t_philosopher	*philosophers;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	int				philosopher_count;
	int				meals_needed;
}					t_simulation;

// Init
void				free_simulation(t_simulation *sim,
						int philosophers_allocated);

// Valid
int					is_integer(const char *str);
int					ft_atoi(const char *str);
int					check_arguments(int argc, char **argv);