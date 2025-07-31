/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:13:54 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/31 15:59:09 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	is_active(t_philosopher *philosopher)
{
	int	active;

	pthread_mutex_lock(philosopher->active_lock);
	active = *(philosopher->active);
	pthread_mutex_unlock(philosopher->active_lock);
	return (active);
}

int	routine_step(t_philosopher *philosopher)
{
	int	result;

	result = 0;
	if (!is_active(philosopher))
		return (1);
	philo_think(philosopher);
	if (!is_active(philosopher))
		return (1);
	philo_take_forks(philosopher);
	if (!is_active(philosopher))
		return (pthread_mutex_unlock(philosopher->left_fork),
			pthread_mutex_unlock(philosopher->right_fork), 1);
	result = philo_eat(philosopher);
	pthread_mutex_unlock(philosopher->left_fork);
	pthread_mutex_unlock(philosopher->right_fork);
	if (result)
		return (2);
	if (!is_active(philosopher))
		return (1);
	philo_sleep(philosopher);
	return (0);
}

void	handle_single_philosopher(t_philosopher *philosopher)
{
	size_t	timestamp;

	pthread_mutex_lock(philosopher->left_fork);
	pthread_mutex_lock(philosopher->write_lock);
	timestamp = get_time();
	printf("%zu %d has taken a fork\n", timestamp, philosopher->id + 1);
	pthread_mutex_unlock(philosopher->write_lock);
	precise_sleep(philosopher->time->to_die);
	pthread_mutex_unlock(philosopher->left_fork);
}

void	*routine(void *args)
{
	t_philosopher	*philosopher;
	int				result;

	philosopher = (t_philosopher *)args;
	result = 0;
	if (philosopher->id % 2 == 0)
		precise_sleep(1);
	if (philosopher->time && philosopher->time->to_die > 0
		&& philosopher->time->to_eat > 0 && philosopher->time->to_sleep > 0
		&& philosopher->meals_needed != 0 && philosopher->write_lock
		&& philosopher->left_fork && philosopher->right_fork
		&& philosopher->active && philosopher->active_lock
		&& philosopher->meal_lock && philosopher->id == 0
		&& philosopher->right_fork == philosopher->left_fork)
	{
		return (handle_single_philosopher(philosopher), NULL);
	}
	while (1)
	{
		result = routine_step(philosopher);
		if (result)
			break ;
	}
	return (NULL);
}
