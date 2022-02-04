/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:46:22 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/04 12:27:12 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_log(t_philo *philo, int ACTION, int id)
{
	uint64_t	t_diff;

	if (philo->info->is_dead == true && ACTION != DEAD)
		return ;
	t_diff = timestamp() - philo->info->start_time;
	if (ACTION == FORK_LEFT)
		printf("%s%-5lld %s %s%d%s %s", BB, t_diff, PH, BR, id, NC, LOG_FORK);
	if (ACTION == FORK_RIGHT)
		printf("%s%-5lld %s %s%d%s %s", BB, t_diff, PH, BR, id, NC, LOG_FORK);
	if (ACTION == EAT)
		printf("%s%-5lld %s %s%d%s %s", BB, t_diff, PH, BR, id, NC, LOG_EAT);
	if (ACTION == SLEEP && philo->meals_eaten != philo->info->n_meals)
		printf("%s%-5lld %s %s%d%s %s", BB, t_diff, PH, BR, id, NC, LOG_SLEEP);
	if (ACTION == THINK && philo->meals_eaten != philo->info->n_meals)
		printf("%s%-5lld %s %s%d%s %s", BB, t_diff, PH, BR, id, NC, LOG_THINK);
	if (ACTION == DEAD)
		printf("%s%-5lld %s %s%d%s %s", BB, t_diff, PH, BR, id, NC, LOG_DEAD);
}

void	check_if_dead(t_philo *philo, t_sim *sim)
{
	uint64_t	time;
	int			i;

	i = 0;
	while (philo->meals_eaten != philo->info->n_meals)
	{
		if (i == sim->n_philo - 1)
			i = 0;
		time = timestamp() - philo[i].t_last_meal;
		if (time >= philo[i].info->to_die)
		{
			pthread_mutex_lock(&philo->info->dead_lock);
			philo[i].info->is_dead = true;
			pthread_mutex_unlock(&philo->info->dead_lock);
			pthread_mutex_unlock(&philo->info->forks_lock[philo->left_fork]);
			print_log(philo, DEAD, philo[i].id);
			return ;
		}
		if (sim->n_philo != 1)
			i++;
	}
}

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

void	create_threads(t_philo *philo, t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % sim->n_philo;
		philo[i].is_eating = 0;
		philo[i].meals_eaten = 0;
		philo[i].info = sim;
	}
	i = -1;
	while (++i < sim->n_philo)
	{
		if ((pthread_create(&sim->philo_thread[i], NULL, &routine, &philo[i])))
			ft_error(ERR_THREAD, sim);
		usleep(50);
	}
	check_if_dead(philo, sim);
	i = -1;
	while (++i < sim->n_philo)
		pthread_join(sim->philo_thread[i], NULL);
}
