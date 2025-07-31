/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:14:13 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/31 15:49:50 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor(void *arg)
{
	t_simulation	*sim;
	int				completed_meals;

	sim = (t_simulation *)arg;
	while (1)
	{
		completed_meals = 0;
		if (monitor_all_philos(sim, &completed_meals))
			return (NULL);
		if (sim->philosophers[0].meals_needed != -1
			&& completed_meals == sim->philosopher_count)
		{
			pthread_mutex_lock(&sim->active_lock);
			*sim->philosophers[0].active = 0;
			pthread_mutex_unlock(&sim->active_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}

/*
HOW TO USE:

./philo
	[num_of_philos]
	[time_to_die]
	[time_to_eat]
	[time_to_sleep]
	[num_of_times_each_philo_must_eat]
*/
int	main(int argc, char **argv)
{
	t_simulation	*sim;
	pthread_t		monitor_thread;

	sim = NULL;
	if (argc < 5)
		return (0);
	if (argc > 6)
		return (0);
	if (check_arguments(argc, argv))
	{
		sim = init(argc, argv);
		if (!sim)
			return (0);
		start_threads(sim);
		pthread_create(&monitor_thread, NULL, monitor, sim);
		join_threads(sim, monitor_thread);
		cleanup_simulation(sim);
		return (1);
	}
	return (0);
}
