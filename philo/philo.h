/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:10:26 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/01 22:07:10 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdbool.h>

# define BB "\e[1;34m"
# define BR "\e[1;31m"
# define GREY = "\033[2;37m"
# define NC "\e[0m"

# define FORK_LEFT 1
# define FORK_RIGHT 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define FULL 6
# define DEAD 7

# define PHILO "\033[2;37mPhilosopher\e[0m"
# define PRINT_LEFT "took his left fork 🍴\n"
# define PRINT_RIGHT "took his right fork 🍴\n"
# define PRINT_EAT "is eating noodles 🍜\n"
# define PRINT_SLEEP "went to sleep and dropped both forks 🌙\n"
# define PRINT_THINK "woke up and is thinking 💬\n"
# define PRINT_DEAD "starved to death 💀\n"

# define ERR_ARG "arguments must be positive numbers"
# define ERR_NO_PHILO "there must be at least 1 philosopher"
# define ERR_USE "usage: [n_philo] [time_to_die] \
[time_to_eat] [time_to_sleep] [n_meals]"
# define ERR_THREAD "failed to create threads"

typedef struct s_sim
{
	int				n_philo;
	int				n_meals;
	uint64_t		to_die;
	uint64_t		to_eat;
	uint64_t		to_sleep;
	uint64_t		t_last_meal;
	bool			is_dead;
	// bool				max_meals;
	uint64_t		start_time;
	pthread_t		*philo_thread;
	pthread_mutex_t	*forks;
}	t_sim;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	t_sim			*sim_state;
}	t_philo;

int			main(int argc, char **argv);
void		create_threads(t_philo *p, t_sim *sim);
uint64_t	timestamp(void);
void		ft_error(char *str);

#endif