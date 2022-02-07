/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:15:30 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/07 20:15:28 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	parse_arg(t_sim *sim, int argc, char **argv)
{
	sim->n_philo = ft_atoi(argv[1]);
	sim->philo_thread = malloc(sizeof(pthread_t) * sim->n_philo);
	sim->forks_lock = malloc(sizeof(pthread_mutex_t) * sim->n_philo);
	if (!sim->philo_thread || !sim->forks_lock)
		return (1);
	if (ft_atoi(argv[2]) >= 0 && ft_atoi(argv[3]) >= 0
		&& ft_atoi(argv[4]) >= 0)
	{
		sim->to_die = ft_atoi(argv[2]);
		sim->to_eat = ft_atoi(argv[3]);
		sim->to_sleep = ft_atoi(argv[4]);
	}
	else
	{
		printf("philo: %s\n", ERR_MAX_INT);
		return (1);
	}
	sim->n_meals = -1;
	if (argc == 6)
		sim->n_meals = ft_atoi(argv[5]);
	sim->start_time = timestamp();
	sim->is_dead = false;
	return (0);
}

int	start_philo(t_philo *philo, t_sim *sim, int argc, char **argv)
{
	int	i;
	int	err;

	err = parse_arg(sim, argc, argv);
	if (!err)
	{
		if (pthread_mutex_init(&sim->dead_lock, NULL))
			err = 3;
		i = -1;
		while (++i < sim->n_philo)
		{
			if (err == 3 || pthread_mutex_init(&sim->forks_lock[i], NULL))
			{
				printf("philo: %s\n", ERR_MUTEX);
				return (1);
			}
		}
	}
	philo = malloc(sizeof(t_philo) * sim->n_philo);
	if (!philo)
		err = 2;
	else if (!err && create_threads(philo, sim))
		err = 2;
	free_philo(philo, sim, err);
	return (err);
}

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (ft_atoi(argv[1]) < 1)
		return (2);
	if (ft_atoi(argv[1]) > 200)
		return (3);
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philo;
	t_sim	sim;
	int		err;

	err = 0;
	philo = NULL;
	if (argc >= 5 && argc <= 6)
	{
		err = check_args(argv);
		if (!err)
			err = start_philo(philo, &sim, argc, argv);
		else if (err == 1)
			printf("philo: %s\n", ERR_ARG);
		else if (err == 2)
			printf("philo: %s\n", ERR_NO_PHILO);
		else if (err == 3)
			printf("philo: %s\n", ERR_MAX_PHILO);
	}
	else
		err = printf("philo: %s\n", ERR_USE);
	if (err != 0)
		return (1);
	return (0);
}
