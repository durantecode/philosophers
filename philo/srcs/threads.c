/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:46:22 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/03 18:46:43 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	print_log(t_philo *philo, int ACTION, int id)
{
	uint64_t time_diff;

	if (philo->sim_state->is_dead && ACTION != DEAD)
		return ;
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
	if (ACTION == DEAD)
		printf("%s%-5lld %s%s %s%d%s %s", BB, time_diff, NC, PHILO, BR, id, NC, PRINT_DEAD);
}

void	check_if_dead(t_philo *philo)
{
	uint64_t time;

	time = timestamp() - philo->sim_state->start_time;
	if (time > philo->sim_state->to_die)
		philo->sim_state->is_dead = true;
}

void	my_usleep(t_philo *philo, uint64_t action_time)
{
	uint64_t	current_time;
	uint64_t	total_time_passed;

	current_time = timestamp();
	total_time_passed = current_time + action_time;
	while (current_time < total_time_passed)
	{
		if (philo->sim_state->is_dead)
			break ;
		current_time = timestamp();
		usleep(action_time);
	}
	(void)philo;
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
	my_usleep(philo, philo->sim_state->to_eat);
	philo->t_last_meal = timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->sim_state->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->sim_state->forks[philo->right_fork]);
	print_log(philo, SLEEP, philo->id);
}

void	think(t_philo *philo)
{
	my_usleep(philo, philo->sim_state->to_sleep);
	print_log(philo, THINK, philo->id);
}

void	*routine(void *arg_p)
{
	t_philo	*philo;

	philo = (t_philo *) arg_p;
	philo->t_last_meal = timestamp();
	while (!philo->sim_state->is_dead && philo->meals_eaten != philo->sim_state->n_meals)
	{
		// if (philo->sim_state->is_dead)
		// 	pthread_mutex_lock(&philo->lock_sim[philo->id]);
		take_forks(philo);
		eat_and_drop_forks(philo);
		// if (philo->sim_state->is_dead)
		// 	break ;
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
		philo[i].meals_eaten = 0;
		philo[i].sim_state = sim;
		// philo[i].t_last_meal = timestamp();
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
	while (1)
	{
		if (i == sim->n_philo - 1)
			i = 0;
		if (timestamp() - philo[i].t_last_meal > philo[i].sim_state->to_die)
		{
			philo[i].sim_state->is_dead = true;
			print_log(philo, DEAD, philo[i].id);
			pthread_mutex_unlock(&philo->sim_state->forks[philo->left_fork]);
			// pthread_mutex_unlock(&philo->sim_state->forks[philo->right_fork]);
			break ;
		}
		if (sim->n_philo != 1)
			i++;
	}
	
	i = 0;
	while (i < sim->n_philo)
	{
		pthread_join(sim->philo_thread[i], NULL);
		i++;
	}
}
