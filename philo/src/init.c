/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:47:22 by dmalasek          #+#    #+#             */
/*   Updated: 2025/03/02 17:22:21 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

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
}

void	init_mutexes(t_simulation *sim)
{
	pthread_mutex_init(&sim->write_lock, NULL);
	pthread_mutex_init(&sim->dead_lock, NULL);
	pthread_mutex_init(&sim->meal_lock, NULL);
}

t_simulation	*init(int argc, char **argv)
{
	t_simulation	*sim;
	int				i;
	int				mutexes_initialized;

	// TODO add error handlers when malloc fails
	i = 0;
	mutexes_initialized = 0;
	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	sim->philosopher_count = ft_atoi(argv[1]);
	if (argc == 6)
		sim->meals_needed = ft_atoi(argv[5]);
	else
		sim->meals_needed = -1;
	init_mutexes(sim);
	sim->philosophers = malloc(sizeof(t_philosopher) * sim->philosopher_count);
	if (!sim->philosophers)
		return (free_simulation(sim, i), NULL);
	while (i < sim->philosopher_count)
	{
		sim->philosophers[i].id = i;
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].time = malloc(sizeof(t_time));
		if (!sim->philosophers[i].time)
			return (free_simulation(sim, i), NULL);
		sim->philosophers[i].time->to_die = ft_atoi(argv[2]);
		sim->philosophers[i].time->to_eat = ft_atoi(argv[3]);
		sim->philosophers[i].time->to_sleep = ft_atoi(argv[4]);
		sim->philosophers[i].time->last_meal = get_time();
		sim->philosophers[i].left_fork = malloc(sizeof(pthread_mutex_t));
		sim->philosophers[i].right_fork = malloc(sizeof(pthread_mutex_t));
		if (!sim->philosophers[i].left_fork || !sim->philosophers[i].right_fork)
			return (free_simulation(sim, i), NULL);
		pthread_mutex_init(sim->philosophers[i].left_fork, NULL);
		pthread_mutex_init(sim->philosophers[i].right_fork, NULL);
		sim->philosophers[i].write_lock = &sim->write_lock;
		sim->philosophers[i].dead_lock = &sim->dead_lock;
		sim->philosophers[i].meal_lock = &sim->meal_lock;
		i++;
	}
	return (sim);
}
