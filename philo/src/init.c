/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidmalasek <davidmalasek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:47:22 by dmalasek          #+#    #+#             */
/*   Updated: 2025/04/08 16:04:45 by davidmalase      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
/*
void	free_simulation(t_simulation *sim, int philosophers_allocated)
{
	int	i;

	if (!sim)
		return ;
	i = 0;
	while (i < philosophers_allocated)
	{
		if (sim->philosophers[i].time)
			free(sim->philosophers[i].time);
		if (sim->philosophers[i].left_fork)
			free(sim->philosophers[i].left_fork);
		if (sim->philosophers[i].right_fork)
			free(sim->philosophers[i].right_fork);
		i++;
	}
	if (sim->philosophers)
		free(sim->philosophers);
	free(sim);
}*/
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

	sim = malloc(sizeof(t_simulation));
	if (!sim)
	{
		// TODO: handle malloc error
	}
	sim->philosopher_count = atoi(argv[1]);
	if (argc == 6)
		sim->meals_needed = atoi(argv[5]);
	else
		sim->meals_needed = -1;
	init_mutexes(sim);
	sim->active = 1;
	sim->philosophers = malloc(sizeof(t_philosopher) * sim->philosopher_count);
	sim->time = malloc(sizeof(t_time));
	if (!sim->time)
	{
		// TODO: handle malloc error
	}
	sim->time->start = get_time();
	sim->time->to_die = atoi(argv[2]);
	sim->time->to_eat = atoi(argv[3]);
	sim->time->to_sleep = atoi(argv[4]);
	if (!sim->philosophers)
	{
		// TODO: handle malloc error
	}
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philosopher_count);
	if (!sim->forks)
	{
		// TODO: handle malloc error
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
		sim->philosophers[i].last_meal = sim->time->start;
		sim->philosophers[i].right_fork = &sim->forks[i];
		sim->philosophers[i].left_fork = &sim->forks[(i + 1)
			% sim->philosopher_count];
		sim->philosophers[i].write_lock = &sim->write_lock;
		sim->philosophers[i].active_lock = &sim->active_lock;
		sim->philosophers[i].meal_lock = &sim->meal_lock;
		i++;
	}
	return (sim);
}
