/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:10:26 by ldurante          #+#    #+#             */
/*   Updated: 2022/02/07 18:35:50 by ldurante         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <stdbool.h>

# define BB "\e[1;34m"
# define BR "\e[1;31m"
# define GREY "\033[2;37m"
# define NC "\e[0m"

# define FORK_LEFT 1
# define FORK_RIGHT 2
# define EAT 3
# define SLEEP 4
# define THINK 5
# define FULL 6
# define DEAD 7

# define PH "\033[2;37mPhilosopher\e[0m"
# define LOG_FORK "has taken a fork 🍴\n"
# define LOG_EAT "is eating 🍜\n"
# define LOG_SLEEP "is sleeping 🌙\n"
# define LOG_THINK "is thinking 💬\n"
# define LOG_DEAD "died 💀\n"

# define ERR_ARG "arguments must be positive numbers"
# define ERR_NO_PHILO "there must be at least 1 philosopher"
# define ERR_MAX_PHILO "number of philos can't exceed 200"
# define ERR_MAX_INT "time can't exceed max int"
# define ERR_USE "usage: [n_philo] [time_to_die] \
[time_to_eat] [time_to_sleep] [n_meals]"
# define ERR_THREAD "failed to create threads"
# define ERR_MUTEX "failed to initiate mutex"

typedef struct s_sim
{
	int				n_philo;
	int				n_meals;
	uint64_t		to_die;
	uint64_t		to_eat;
	uint64_t		to_sleep;
	bool			is_dead;
	pthread_mutex_t	dead_lock;
	uint64_t		start_time;
	pthread_t		*philo_thread;
	pthread_mutex_t	*forks_lock;
}	t_sim;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				is_eating;
	int				meals_eaten;
	uint64_t		t_last_meal;
	t_sim			*info;
}	t_philo;

int			main(int argc, char **argv);
void		free_philo(t_philo *philo, t_sim *sim);
int			create_threads(t_philo *p, t_sim *sim);
void		*routine(void *arg_p);
uint64_t	timestamp(void);
void		print_log(t_philo *philo, int ACTION, int id);
void		my_usleep(t_philo *philo, uint64_t action_time);
int			ft_atoi(const char *str);
int			ft_isdigit(int c);

#endif