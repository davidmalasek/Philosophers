/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmalasek <dmalasek@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 10:52:17 by dmalasek          #+#    #+#             */
/*   Updated: 2025/03/02 14:44:20 by dmalasek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
