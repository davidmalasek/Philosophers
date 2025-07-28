/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:47:22 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/28 18:14:33 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * Initializes mutexes.
 */
void	init_mutexes(t_simulation *sim)
{
	pthread_mutex_init(&sim->write_lock, NULL);
	pthread_mutex_init(&sim->active_lock, NULL);
	pthread_mutex_init(&sim->meal_lock, NULL);
}
/**
 * Initalizes the whole simulation.
 */
t_simulation	*init(int argc, char **argv)
{
	t_simulation	*sim;
	int				i;
	int				meals_needed;

	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	sim->philosopher_count = atoi(argv[1]);
	meals_needed = -1;
	if (argc == 6)
		meals_needed = atoi(argv[5]);
	init_mutexes(sim);
	sim->active = 1;
	sim->philosophers = malloc(sizeof(t_philosopher) * sim->philosopher_count);
	if (!sim->philosophers)
	{
		pthread_mutex_destroy(&sim->write_lock);
		pthread_mutex_destroy(&sim->active_lock);
		pthread_mutex_destroy(&sim->meal_lock);
		free(sim);
		return (NULL);
	}
	sim->philosophers->time = malloc(sizeof(t_time));
	if (!sim->philosophers->time)
	{
		pthread_mutex_destroy(&sim->write_lock);
		pthread_mutex_destroy(&sim->active_lock);
		pthread_mutex_destroy(&sim->meal_lock);
		free(sim->philosophers);
		free(sim);
		return (NULL);
	}
	sim->philosophers->time->start = get_time();
	sim->philosophers->time->to_die = atoi(argv[2]);
	sim->philosophers->time->to_eat = atoi(argv[3]);
	sim->philosophers->time->to_sleep = atoi(argv[4]);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philosopher_count);
	if (!sim->forks)
	{
		pthread_mutex_destroy(&sim->write_lock);
		pthread_mutex_destroy(&sim->active_lock);
		pthread_mutex_destroy(&sim->meal_lock);
		free(sim->philosophers);
		free(sim->philosophers->time);
		free(sim);
		return (NULL);
	}
	i = 0;
	while (i < sim->philosopher_count)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i++;
	}
	i = 0;
	while (i < sim->philosopher_count)
	{
		sim->philosophers[i].id = i;
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].last_meal = sim->philosophers->time->start;
		sim->philosophers[i].right_fork = &sim->forks[i];
		sim->philosophers[i].left_fork = &sim->forks[(i + 1)
			% sim->philosopher_count];
		sim->philosophers[i].write_lock = &sim->write_lock;
		sim->philosophers[i].active_lock = &sim->active_lock;
		sim->philosophers[i].meal_lock = &sim->meal_lock;
		sim->philosophers[i].active = &sim->active;
		sim->philosophers[i].meals_needed = meals_needed;
		sim->philosophers[i].time = sim->philosophers->time;
		i++;
	}
	return (sim);
}
