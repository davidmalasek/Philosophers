/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:52:17 by dmalasek          #+#    #+#             */
/*   Updated: 2025/07/29 13:10:07 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

size_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	init_mutexes(t_simulation *sim)
{
	pthread_mutex_init(&sim->write_lock, NULL);
	pthread_mutex_init(&sim->active_lock, NULL);
	pthread_mutex_init(&sim->meal_lock, NULL);
}

int	check_arguments(int argc, char **argv)
{
	int	i;

	i = 1;
	while (i < argc)
	{
		if (!is_integer(argv[i]))
			return (0);
		else if (i == 1 && ft_atoi(argv[i]) > 200)
			return (0);
		else if (i < 5 && ft_atoi(argv[i]) <= 0)
			return (0);
		else if (i == 5 && ft_atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}

void	precise_sleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(500);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while ((*str == ' ' || *str == '\f') || (*str == '\n' || *str == '\r')
		|| (*str == '\t' || *str == '\v'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}
