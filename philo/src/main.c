/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:39:26 by davidmalase       #+#    #+#             */
/*   Updated: 2025/02/03 11:57:01 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * Checks if arguments are valid.
 * Valid argument is a number.
 * Argument 1-4 must be greater than 0.
 * Argument of index 1 (num of philosophers) cannot
 * be bigger than 200.
 * Argument of index 5 can be equal to 0
 */
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

/**
 * argv[0] / ./philo
 * argv[1] - number_of_philosophers
 * argv[2] - time_to_die
 * argv[3] - time_to_eat
 * argv[4] - time_to_sleep
 * argv[5] - number_of_times_each_philosopher_must_eat (optional)
 */
int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	if (argc == 5 || argc == 6)
	{
		if (!check_arguments(argc, argv))
			return (0);
	}
}
