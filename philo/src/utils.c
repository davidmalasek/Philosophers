/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: davidmalasek <davidmalasek@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:52:17 by dmalasek          #+#    #+#             */
/*   Updated: 2025/04/08 16:02:05 by davidmalase      ###   ########.fr       */
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
		else if (i == 1 && atoi(argv[i]) > 200)
			return (0);
		else if (i < 5 && atoi(argv[i]) <= 0)
			return (0);
		else if (i == 5 && atoi(argv[i]) < 0)
			return (0);
		i++;
	}
	return (1);
}
