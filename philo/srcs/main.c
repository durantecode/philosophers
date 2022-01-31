/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:15:30 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/31 12:54:59 by ldurante         ###   ########.fr       */
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
	printf("%s %s\n", PHILO, ERR);
	exit (0);
}

int		parse_arg(t_sim *sim, int argc, char **argv)
{
	int i;

	sim->n_philo = ft_atoi(argv[1]);
	sim->to_die = ft_atoi(argv[2]);
	sim->to_eat = ft_atoi(argv[3]);
	sim->to_sleep = ft_atoi(argv[4]);
	sim->n_meals = 0;
	if (argc == 6)
		sim->n_meals = ft_atoi(argv[5]);
	sim->start_time = timestamp();
	sim->philo_thread = malloc(sizeof(pthread_t) * sim->n_philo);
	sim->forks = malloc(sizeof(pthread_mutex_t) * sim->n_philo);
	i = 0;
	while (i < sim->n_philo)
	{
		if (pthread_mutex_init(&sim->forks[i], NULL))
			return (1);
		i++;
	}
	return (0);
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

	// p.start_time = timestamp();
	if (argc >= 5 && argc <= 6)
	{
		if (!check_args(argv))
		{
			parse_arg(&sim, argc, argv);
			philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
			create_threads(philo, &sim);
			i = 0;
			// while (i < sim.n_philo)
			// {
			// 	pthread_mutex_destroy(&sim.forks[i]);
			// 	pthread_mutex_destroy(philo[i].eat);
			// 	i++;
			// }
		}
		else
			printf("%s %s\n", PHILO, ERR_ARG);
	}
	else
		printf("%s %s\n", PHILO, ERR_USE);
	// p.end_time = timestamp();
	// printf("TIME: %lldms\n", p.end_time - p.start_time);
	return (0);
}