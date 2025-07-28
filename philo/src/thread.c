/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 19:45:39 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/28 20:04:45 by dmalasek         ###   ########.fr       */
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
		i = i + 1;
	}
}

void	join_threads(t_simulation *sim, pthread_t monitor_thread)
{
	int	i;
	int	ret;

	i = 0;
	while (i < sim->philosopher_count)
	{
		ret = pthread_join(sim->philosophers[i].thread, NULL);
		if (ret != 0)
			pthread_cancel(sim->philosophers[i].thread);
		i = i + 1;
	}
	pthread_join(monitor_thread, NULL);
}
