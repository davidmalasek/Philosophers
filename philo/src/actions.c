/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:56:01 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/29 13:43:55 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_think(t_philosopher *philosopher)
{
	int	active;

	pthread_mutex_lock(philosopher->write_lock);
	pthread_mutex_lock(philosopher->active_lock);
	active = *(philosopher->active);
	pthread_mutex_unlock(philosopher->active_lock);
	if (active)
		printf("[%zu] %d is thinking\n", get_time(), philosopher->id + 1);
	pthread_mutex_unlock(philosopher->write_lock);
}

static void	print_fork_taken(t_philosopher *philosopher)
{
	size_t	timestamp;

	timestamp = get_time();
	if (*(philosopher->active))
		printf("[%zu] %d has taken a fork\n", timestamp, philosopher->id + 1);
}

void	philo_take_forks(t_philosopher *philosopher)
{
	if (philosopher->id % 2 == 0)
	{
		pthread_mutex_lock(philosopher->left_fork);
		pthread_mutex_lock(philosopher->write_lock);
		print_fork_taken(philosopher);
		pthread_mutex_unlock(philosopher->write_lock);
		pthread_mutex_lock(philosopher->right_fork);
		pthread_mutex_lock(philosopher->write_lock);
		print_fork_taken(philosopher);
		pthread_mutex_unlock(philosopher->write_lock);
	}
	else
	{
		pthread_mutex_lock(philosopher->right_fork);
		pthread_mutex_lock(philosopher->write_lock);
		print_fork_taken(philosopher);
		pthread_mutex_unlock(philosopher->write_lock);
		pthread_mutex_lock(philosopher->left_fork);
		pthread_mutex_lock(philosopher->write_lock);
		print_fork_taken(philosopher);
		pthread_mutex_unlock(philosopher->write_lock);
	}
}

int	philo_eat(t_philosopher *philosopher)
{
	int	active;

	pthread_mutex_lock(philosopher->meal_lock);
	philosopher->last_meal = get_time();
	pthread_mutex_unlock(philosopher->meal_lock);
	pthread_mutex_lock(philosopher->write_lock);
	pthread_mutex_lock(philosopher->active_lock);
	active = *(philosopher->active);
	pthread_mutex_unlock(philosopher->active_lock);
	if (active)
		printf("[%zu] %d is eating\n", get_time(), philosopher->id + 1);
	pthread_mutex_unlock(philosopher->write_lock);
	precise_sleep(philosopher->time->to_eat);
	philosopher->meals_eaten++;
	if (philosopher->meals_needed != -1
		&& philosopher->meals_eaten == philosopher->meals_needed)
	{
		pthread_mutex_unlock(philosopher->left_fork);
		pthread_mutex_unlock(philosopher->right_fork);
		return (1);
	}
	return (0);
}

void	philo_sleep(t_philosopher *philosopher)
{
	int	active;

	pthread_mutex_lock(philosopher->write_lock);
	pthread_mutex_lock(philosopher->active_lock);
	active = *(philosopher->active);
	pthread_mutex_unlock(philosopher->active_lock);
	if (active)
		printf("[%zu] %d is sleeping\n", get_time(), philosopher->id + 1);
	pthread_mutex_unlock(philosopher->write_lock);
	precise_sleep(philosopher->time->to_sleep);
}
