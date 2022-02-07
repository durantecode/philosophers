/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:40:34 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/07 18:07:14 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->forks_lock[philo->left_fork]);
	print_log(philo, FORK_LEFT, philo->id);
	pthread_mutex_lock(&philo->info->forks_lock[philo->right_fork]);
	print_log(philo, FORK_RIGHT, philo->id);
	print_log(philo, EAT, philo->id);
	philo->t_last_meal = timestamp();
	philo->meals_eaten++;
	my_usleep(philo, philo->info->to_eat);
	pthread_mutex_unlock(&philo->info->forks_lock[philo->left_fork]);
	pthread_mutex_unlock(&philo->info->forks_lock[philo->right_fork]);
	print_log(philo, SLEEP, philo->id);
	my_usleep(philo, philo->info->to_sleep);
	print_log(philo, THINK, philo->id);
}

void	*routine(void *arg_p)
{
	t_philo	*philo;

	philo = (t_philo *) arg_p;
	philo->t_last_meal = timestamp();
	pthread_mutex_lock(&philo->info->dead_lock);
	while (!philo->info->is_dead && philo->meals_eaten != philo->info->n_meals)
	{
		pthread_mutex_unlock(&philo->info->dead_lock);
		philo_routine(philo);
		pthread_mutex_lock(&philo->info->dead_lock);
	}
	pthread_mutex_unlock(&philo->info->dead_lock);
	return (0);
}
