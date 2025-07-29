/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:45:39 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/29 13:03:31 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	start_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	while (i < sim->philosopher_count)
	{
		pthread_create(&sim->philosophers[i].thread, NULL, routine,
			&sim->philosophers[i]);
		i++;
	}
}

void	join_threads(t_simulation *sim, pthread_t monitor_thread)
{
	int	i;

	i = 0;
	while (i < sim->philosopher_count)
	{
		pthread_join(sim->philosophers[i].thread, NULL);
		i++;
	}
	pthread_join(monitor_thread, NULL);
}
