/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:15:30 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/04 12:34:13 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	leaks(void)
{
	system("leaks -q philo");
}

void	parse_arg(t_sim *sim, int argc, char **argv)
{
	int	i;

	sim->n_philo = ft_atoi(argv[1]);
	sim->to_die = ft_atoi(argv[2]);
	sim->to_eat = ft_atoi(argv[3]);
	sim->to_sleep = ft_atoi(argv[4]);
	sim->n_meals = -1;
	if (argc == 6)
		sim->n_meals = ft_atoi(argv[5]);
	sim->start_time = timestamp();
	sim->is_dead = false;
	sim->philo_thread = malloc(sizeof(pthread_t) * sim->n_philo);
	sim->forks_lock = malloc(sizeof(pthread_mutex_t) * sim->n_philo);
	if (pthread_mutex_init(&sim->dead_lock, NULL))
		ft_error(ERR_MUTEX, sim);
	i = 0;
	while (i < sim->n_philo)
	{
		if (pthread_mutex_init(&sim->forks_lock[i], NULL))
			ft_error(ERR_MUTEX, sim);
		i++;
	}
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

	if (argc >= 5 && argc <= 6)
	{
		err = check_args(argv);
		if (!err)
		{
			parse_arg(&sim, argc, argv);
			philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
			create_threads(philo, &sim);
			free_philo(philo, &sim);
		}
		else if (err == 1)
			printf("philo: %s\n", ERR_ARG);
		else if (err == 2)
			printf("philo: %s\n", ERR_NO_PHILO);
		else if (err == 3)
			printf("philo: %s\n", ERR_MAX_PHILO);
	}
	else
		printf("philo: %s\n", ERR_USE);
	return (0);
}
