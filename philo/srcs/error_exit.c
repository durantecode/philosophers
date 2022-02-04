/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 11:06:53 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/04 12:22:54 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	free_philo(t_philo *philo, t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->n_philo)
		pthread_mutex_destroy(&sim->forks_lock[i]);
	pthread_mutex_destroy(&sim->dead_lock);
	free(sim->philo_thread);
	free(sim->forks_lock);
	free(philo);
}

void	ft_error(char *ERR, t_sim *sim)
{
	printf("philo: %s\n", ERR);
	free(sim->philo_thread);
	free(sim->forks_lock);
	exit (0);
}
