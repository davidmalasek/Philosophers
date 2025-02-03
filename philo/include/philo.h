/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:22:52 by dmalasek          #+#    #+#             */
/*   Updated: 2025/02/03 14:12:42 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>

typedef struct s_simulation
{
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_die;
}					t_simulation;

typedef struct s_time
{
	long			since_born;
	long			to_eat;
	long			to_sleep;
	long			to_die;
}					t_time;

typedef struct s_philosopher
{
	pthread_t		thread;
	int				id;
	int				meal_count;
	t_time			*time;
	t_simulation	*simulation;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
}					t_philosopher;

// Valid
int					is_integer(const char *str);
int					ft_atoi(const char *str);