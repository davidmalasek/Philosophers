/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:13:54 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/28 20:33:26 by dmalasek         ###   ########.fr       */
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

void	*routine(void *args)
{
	t_philosopher	*philosopher;
	int				result;

	philosopher = (t_philosopher *)args;
	result = 0;
	if (philosopher->id % 2 == 0)
		precise_sleep(1);
	while (1)
	{
		result = routine_step(philosopher);
		if (result)
			break ;
	}
	return (NULL);
}
