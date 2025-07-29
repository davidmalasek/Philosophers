/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:14:13 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/29 13:10:47 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor(void *arg)
{
	t_simulation	*sim;
	int				full;

	sim = (t_simulation *)arg;
	while (1)
	{
		full = 0;
		if (monitor_all_philos(sim, &full))
			return (NULL);
		if (sim->philosophers[0].meals_needed != -1
			&& full == sim->philosopher_count)
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

int	main(int argc, char **argv)
{
	t_simulation	*sim;
	int				ok;
	pthread_t		monitor_thread;

	sim = NULL;
	ok = 0;
	if (argc < 5)
		return (0);
	if (argc > 6)
		return (0);
	ok = check_arguments(argc, argv);
	if (ok)
	{
		sim = init(argc, argv);
		if (!sim)
			return (1);
		start_threads(sim);
		pthread_create(&monitor_thread, NULL, monitor, sim);
		join_threads(sim, monitor_thread);
		cleanup_simulation(sim);
		return (0);
	}
	return (0);
}

/*
TODO:
- nefunguje exit vzdy
*/