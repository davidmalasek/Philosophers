/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:42:08 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/28 20:04:00 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_philo_full(t_philosopher *philo)
{
	if (philo->meals_needed != -1 && philo->meals_eaten >= philo->meals_needed)
		return (1);
	return (0);
}

int	check_philo_dead(t_philosopher *philo, size_t now)
{
	if (now - philo->last_meal > philo->time->to_die)
		return (1);
	return (0);
}

void	handle_philo_death(t_simulation *sim, int i, size_t now)
{
	pthread_mutex_lock(sim->philosophers[i].write_lock);
	printf("%zu %d died\n", now, sim->philosophers[i].id + 1);
	pthread_mutex_unlock(sim->philosophers[i].write_lock);
	pthread_mutex_lock(&sim->active_lock);
	*sim->philosophers[i].active = 0;
	pthread_mutex_unlock(&sim->active_lock);
	pthread_mutex_unlock(sim->philosophers[i].meal_lock);
}

int	monitor_philo(t_simulation *sim, int i, int *full)
{
	size_t	now;

	pthread_mutex_lock(sim->philosophers[i].meal_lock);
	now = get_time();
	if (check_philo_full(&sim->philosophers[i]))
	{
		*full = *full + 1;
		pthread_mutex_unlock(sim->philosophers[i].meal_lock);
		return (0);
	}
	if (check_philo_dead(&sim->philosophers[i], now))
	{
		handle_philo_death(sim, i, now);
		return (1);
	}
	pthread_mutex_unlock(sim->philosophers[i].meal_lock);
	return (0);
}

int	monitor_all_philos(t_simulation *sim, int *full)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
	while (i < sim->philosopher_count)
	{
		if (monitor_philo(sim, i, full))
			result = 1;
		if (result)
			break ;
		i = i + 1;
	}
	return (result);
}
