/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:43:45 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/30 16:51:31 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*cleanup_on_error(t_simulation *sim, int stage)
{
	if (stage >= 1)
		pthread_mutex_destroy(&sim->write_lock);
	if (stage >= 2)
		pthread_mutex_destroy(&sim->active_lock);
	if (stage >= 3)
		pthread_mutex_destroy(&sim->meal_lock);
	if (stage >= 4)
		free(sim->philosophers);
	if (stage >= 5)
		free(sim->philosophers->time);
	if (stage >= 6)
		free(sim);
	return (NULL);
}

void	cleanup_simulation(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->philosopher_count)
	{
		pthread_mutex_destroy(&sim->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&sim->write_lock);
	pthread_mutex_destroy(&sim->active_lock);
	pthread_mutex_destroy(&sim->meal_lock);
	free(sim->forks);
	free(sim->philosophers->time);
	free(sim->philosophers);
	free(sim);
}
