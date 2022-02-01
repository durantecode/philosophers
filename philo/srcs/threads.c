/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:46:22 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/01 03:47:08 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	my_usleep(uint64_t action_time)
{
	uint64_t	current_time;
	uint64_t	total_time_passed;

	current_time = timestamp();
	total_time_passed = current_time + action_time;
	while (current_time < total_time_passed)
	{
		current_time = timestamp();
		usleep(action_time);
	}
}

void	print_log(t_philo *philo, int ACTION, int id)
{
	uint64_t time_diff;

	time_diff = timestamp() - philo->sim_state->start_time;
	if (ACTION == FORK_LEFT)
		printf("%s%-5lld %s%s %s%d%s %s", BB, time_diff, NC, PHILO, BR, id, NC, PRINT_LEFT);
	if (ACTION == FORK_RIGHT)
		printf("%s%-5lld %s%s %s%d%s %s", BB, time_diff, NC, PHILO, BR, id, NC, PRINT_RIGHT);
	if (ACTION == EAT)
		printf("%s%-5lld %s%s %s%d%s %s", BB, time_diff, NC, PHILO, BR, id, NC, PRINT_EAT);
	if (ACTION == SLEEP)
		printf("%s%-5lld %s%s %s%d%s %s", BB, time_diff, NC, PHILO, BR, id, NC, PRINT_SLEEP);
	if (ACTION == THINK)
		printf("%s%-5lld %s%s %s%d%s %s", BB, time_diff, NC, PHILO, BR, id, NC, PRINT_THINK);
	if (ACTION == FULL)
		printf("%s%-5lld %s%s %d meals\n", BB, time_diff, NC, PRINT_FULL, philo->meals_eaten);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim_state->forks[philo->left_fork]);
	print_log(philo, FORK_LEFT, philo->id);
	pthread_mutex_lock(&philo->sim_state->forks[philo->right_fork]);
	print_log(philo, FORK_RIGHT, philo->id);
}

void	eat_and_drop_forks(t_philo *philo)
{
	print_log(philo, EAT, philo->id);
	my_usleep(philo->sim_state->to_eat);
	philo->meals_eaten++;
	print_log(philo, SLEEP, philo->id);
	pthread_mutex_unlock(&philo->sim_state->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->sim_state->forks[philo->right_fork]);
}

void	think(t_philo *philo)
{
	my_usleep(philo->sim_state->to_sleep);
	print_log(philo, THINK, philo->id);
}

void	*routine(void *arg_p)
{
	t_philo	*philo;

	philo = (t_philo *) arg_p;
	philo->meals_eaten = 0;
	while (1)
	{
		take_forks(philo);
		
		eat_and_drop_forks(philo);
		if (philo->meals_eaten == philo->sim_state->n_meals)
			break ;
		think(philo);
	}
	return (0);
}

void	create_threads(t_philo *philo, t_sim *sim)
{
	int i;

	i = 0;
	while (i < sim->n_philo)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % sim->n_philo;
		philo[i].sim_state = sim;
		i++;
	}
	i = 0;
	while (i < sim->n_philo)
	{
		if ((pthread_create(&sim->philo_thread[i], NULL, &routine, &philo[i])))
			ft_error(ERR_THREAD);
		usleep(50);
		i++;
	}
	i = 0;
	while (i < sim->n_philo)
	{
		pthread_join(sim->philo_thread[i], NULL);
		i++;
	}
}
