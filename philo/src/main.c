/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 17:14:13 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/28 18:29:21 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * argv[0] / ./philo
 * argv[1] - number_of_philosophers
 * argv[2] - time_to_die
 * argv[3] - time_to_eat
 * argv[4] - time_to_sleep
 * argv[5] - number_of_times_each_philosopher_must_eat (optional)
 */
static void	*monitor(void *arg)
{
	t_simulation	*sim;
	int				i;
	int				full;
	size_t			now;

	sim = (t_simulation *)arg;
	while (1)
	{
		full = 0;
		i = 0;
		while (i < sim->philosopher_count)
		{
			pthread_mutex_lock(sim->philosophers[i].meal_lock);
			now = get_time();
			if (sim->philosophers[i].meals_needed != -1
				&& sim->philosophers[i].meals_eaten >= sim->philosophers[i].meals_needed)
			{
				full++;
				pthread_mutex_unlock(sim->philosophers[i].meal_lock);
				i++;
				continue ;
			}
			if (now
				- sim->philosophers[i].last_meal > sim->philosophers[i].time->to_die)
			{
				pthread_mutex_lock(sim->philosophers[i].write_lock);
				printf("%zu %d died\n", now, sim->philosophers[i].id + 1);
				pthread_mutex_unlock(sim->philosophers[i].write_lock);
				pthread_mutex_lock(&sim->active_lock);
				*sim->philosophers[i].active = 0;
				pthread_mutex_unlock(&sim->active_lock);
				pthread_mutex_unlock(sim->philosophers[i].meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(sim->philosophers[i].meal_lock);
			i++;
		}
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
	int				i;
	pthread_t		monitor_thread;

	if (argc < 5 || argc > 6)
		return (0);
	if ((argc == 5 || argc == 6) && check_arguments(argc, argv))
	{
		sim = init(argc, argv);
		if (!sim)
			return (1);
		// Start philosopher threads
		i = 0;
		while (i < sim->philosopher_count)
		{
			pthread_create(&sim->philosophers[i].thread, NULL, routine,
				&sim->philosophers[i]);
			i++;
		}
		// Start monitor thread
		pthread_create(&monitor_thread, NULL, monitor, sim);
		// Join philosopher threads
		i = 0;
		while (i < sim->philosopher_count)
		{
			pthread_join(sim->philosophers[i].thread, NULL);
			i++;
		}
		pthread_join(monitor_thread, NULL);
		// Resource cleanup
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
}

/*
TODO:
- no ft_*, libft not allowed
*/
/*
TODO:
- no ft_*, libft not allowed
*/
