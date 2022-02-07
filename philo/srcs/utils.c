/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:53:02 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/07 17:45:54 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	long	number;
	int		negative;

	number = 0;
	negative = 1;
	while ((*str == ' ') || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = -negative;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		if (number * negative > 2147483647)
			return (-1);
		if (number * negative < -2147483648)
			return (0);
		number = number * 10 + *str - 48;
		str++;
	}
	return (number * negative);
}
