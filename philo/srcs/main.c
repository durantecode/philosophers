/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:15:30 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/03 21:33:20 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

uint64_t	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	ft_error(char *ERR)
{
	printf("philo: %s\n", ERR);
	exit (0);
}

void	parse_arg(t_sim *sim, int argc, char **argv)
{
	int i;

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
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->n_philo);
	sim->eating = malloc(sizeof(pthread_mutex_t) * sim->n_philo);
	i = 0;
	while (i < sim->n_philo)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL))
			ft_error(ERR_MUTEX);
		if (pthread_mutex_init(&sim->eating[i], NULL))
			ft_error(ERR_MUTEX);
		i++;
	}
}

int	check_args(char **argv)
{
	int	i;
	int j;

	i = 1;
	if (ft_atoi(argv[1]) < 1)
		ft_error(ERR_NO_PHILO);
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
	int		i;

	if (argc >= 5 && argc <= 6)
	{
		if (!check_args(argv))
		{
			parse_arg(&sim, argc, argv);
			philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
			create_threads(philo, &sim);
			i = 0;
			while (i < sim.n_philo)
			{
				pthread_mutex_destroy(&sim.forks[i]);
				pthread_mutex_destroy(&sim.eating[i]);
				i++;
			}
		}
		else
			printf("philo: %s\n", ERR_ARG);
	}
	else
		printf("philo: %s\n", ERR_USE);
	return (0);
}