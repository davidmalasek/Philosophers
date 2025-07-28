/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:13:54 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/28 18:30:08 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*routine(void *args)
{
	t_philosopher	*philosopher;
	int				active;

	philosopher = (t_philosopher *)args;
	if (philosopher->id % 2 == 0)
		precise_sleep(1); // small stagger for even philosophers
	while (1)
	{
		pthread_mutex_lock(philosopher->active_lock);
		active = *(philosopher->active);
		pthread_mutex_unlock(philosopher->active_lock);
		if (!active)
			break ;
		pthread_mutex_lock(philosopher->write_lock);
		pthread_mutex_lock(philosopher->active_lock);
		active = *(philosopher->active);
		pthread_mutex_unlock(philosopher->active_lock);
		if (active)
			printf("%zu %d is thinking\n", get_time(), philosopher->id + 1);
		pthread_mutex_unlock(philosopher->write_lock);
		if (philosopher->id % 2 == 0)
		{
			pthread_mutex_lock(philosopher->left_fork);
			pthread_mutex_lock(philosopher->write_lock);
			printf("%zu %d has taken a fork\n", get_time(), philosopher->id
				+ 1);
			pthread_mutex_unlock(philosopher->write_lock);
			pthread_mutex_lock(philosopher->right_fork);
			pthread_mutex_lock(philosopher->write_lock);
			printf("%zu %d has taken a fork\n", get_time(), philosopher->id
				+ 1);
			pthread_mutex_unlock(philosopher->write_lock);
		}
		else
		{
			pthread_mutex_lock(philosopher->right_fork);
			pthread_mutex_lock(philosopher->write_lock);
			printf("%zu %d has taken a fork\n", get_time(), philosopher->id
				+ 1);
			pthread_mutex_unlock(philosopher->write_lock);
			pthread_mutex_lock(philosopher->left_fork);
			pthread_mutex_lock(philosopher->write_lock);
			printf("%zu %d has taken a fork\n", get_time(), philosopher->id
				+ 1);
			pthread_mutex_unlock(philosopher->write_lock);
		}
		pthread_mutex_lock(philosopher->meal_lock);
		philosopher->last_meal = get_time();
		pthread_mutex_unlock(philosopher->meal_lock);
		pthread_mutex_lock(philosopher->write_lock);
		pthread_mutex_lock(philosopher->active_lock);
		active = *(philosopher->active);
		pthread_mutex_unlock(philosopher->active_lock);
		if (active)
			printf("%zu %d is eating\n", get_time(), philosopher->id + 1);
		pthread_mutex_unlock(philosopher->write_lock);
		precise_sleep(philosopher->time->to_eat);
		philosopher->meals_eaten++;
		if (philosopher->meals_needed != -1
			&& philosopher->meals_eaten == philosopher->meals_needed)
		{
			pthread_mutex_unlock(philosopher->left_fork);
			pthread_mutex_unlock(philosopher->right_fork);
			return (NULL); // <-- exit immediately after last meal
		}
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
		pthread_mutex_lock(philosopher->active_lock);
		active = *(philosopher->active);
		pthread_mutex_unlock(philosopher->active_lock);
		if (!active)
			break ;
		pthread_mutex_lock(philosopher->write_lock);
		pthread_mutex_lock(philosopher->active_lock);
		active = *(philosopher->active);
		pthread_mutex_unlock(philosopher->active_lock);
		if (active)
			printf("%zu %d is sleeping\n", get_time(), philosopher->id + 1);
		pthread_mutex_unlock(philosopher->write_lock);
		precise_sleep(philosopher->time->to_sleep);
	}
	return (NULL);
}
