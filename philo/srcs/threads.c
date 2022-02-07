/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:46:22 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/07 20:18:58 by ldurante         ###   ########.fr       */
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

void	init_philos(t_philo *philo, t_sim *sim)
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
}

int	create_threads(t_philo *philo, t_sim *sim)
{
	int	i;

	init_philos(philo, sim);
	i = -1;
	while (++i < sim->n_philo)
	{
		if ((pthread_create(&sim->philo_thread[i], NULL, &routine, &philo[i])))
		{	
			printf("philo: %s\n", ERR_THREAD);
			return (1);
		}
		usleep(210);
	}
	check_if_dead(philo, sim);
	i = -1;
	while (++i < sim->n_philo)
		pthread_join(sim->philo_thread[i], NULL);
	return (0);
}
