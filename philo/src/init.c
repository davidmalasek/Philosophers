/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 14:47:22 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/29 13:11:20 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	alloc_philosophers(t_simulation *sim, char **argv)
{
	int	ok;

	ok = 1;
	sim->philosophers = malloc(sizeof(t_philosopher) * sim->philosopher_count);
	if (!sim->philosophers)
		ok = 0;
	if (ok)
	{
		sim->philosophers->time = malloc(sizeof(t_time));
		if (!sim->philosophers->time)
			ok = 0;
	}
	if (ok)
	{
		sim->philosophers->time->start = get_time();
		sim->philosophers->time->to_die = ft_atoi(argv[2]);
		sim->philosophers->time->to_eat = ft_atoi(argv[3]);
		sim->philosophers->time->to_sleep = ft_atoi(argv[4]);
	}
	return (ok);
}

int	alloc_forks(t_simulation *sim)
{
	int	i;

	i = 0;
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->philosopher_count);
	if (!sim->forks)
		return (0);
	while (i < sim->philosopher_count)
	{
		pthread_mutex_init(&sim->forks[i], NULL);
		i = i + 1;
	}
	return (1);
}

void	setup_philosophers(t_simulation *sim, int meals_needed)
{
	int	i;
	int	count;

	i = 0;
	count = sim->philosopher_count;
	while (i < count)
	{
		sim->philosophers[i].id = i;
		sim->philosophers[i].meals_eaten = 0;
		sim->philosophers[i].last_meal = sim->philosophers->time->start;
		sim->philosophers[i].right_fork = &sim->forks[i];
		sim->philosophers[i].left_fork = &sim->forks[(i + 1) % count];
		sim->philosophers[i].write_lock = &sim->write_lock;
		sim->philosophers[i].active_lock = &sim->active_lock;
		sim->philosophers[i].meal_lock = &sim->meal_lock;
		sim->philosophers[i].active = &sim->active;
		sim->philosophers[i].meals_needed = meals_needed;
		sim->philosophers[i].time = sim->philosophers->time;
		i = i + 1;
	}
}

t_simulation	*init(int argc, char **argv)
{
	t_simulation	*sim;
	int				meals_needed;
	int				ok;

	sim = NULL;
	meals_needed = -1;
	sim = malloc(sizeof(t_simulation));
	if (!sim)
		return (NULL);
	sim->philosopher_count = ft_atoi(argv[1]);
	if (argc == 6)
		meals_needed = ft_atoi(argv[5]);
	init_mutexes(sim);
	sim->active = 1;
	ok = alloc_philosophers(sim, argv);
	if (!ok)
		return (cleanup_on_error(sim, 4));
	ok = alloc_forks(sim);
	if (!ok)
		return (cleanup_on_error(sim, 6));
	setup_philosophers(sim, meals_needed);
	return (sim);
}
