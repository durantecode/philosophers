/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 10:50:44 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/04 10:51:15 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

uint64_t	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	my_usleep(t_philo *philo, uint64_t action_time)
{
	uint64_t	current_time;
	uint64_t	total_time_passed;

	current_time = timestamp();
	total_time_passed = current_time + action_time;
	while (current_time < total_time_passed)
	{
		if (philo->info->is_dead)
			break ;
		current_time = timestamp();
		usleep(action_time);
	}
}
