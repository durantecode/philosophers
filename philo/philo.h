/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldurante <ldurante@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 19:10:26 by ldurante          #+#    #+#             */
/*   Updated: 2022/01/31 12:29:37 by ldurante         ###   ########.fr       */
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

# define PHILO "philo:"
# define ERR_ARG "arguments must be numbers"
# define ERR_NO_PHILO "there must be at least 1 philosopher"
# define ERR_USE "usage: [n_philo] [time_to_die] \
[time_to_eat] [time_to_sleep] [n_meals]"
# define ERR_THREAD "failed to create threads"

typedef struct s_sim
{
	int				n_philo;
	int				n_meals;
	uint64_t		start_time;
	uint64_t		end_time;
	uint64_t		to_die;
	uint64_t		to_eat;
	uint64_t		to_sleep;
	bool			is_dead;
	pthread_t		*philo_thread;
	pthread_mutex_t	*forks;
	pthread_mutex_t	sleep;
	pthread_mutex_t	meals;
}	t_sim;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				right_fork;
	int				meals_eaten;
	pthread_mutex_t	*eat;
	t_sim			*sim_state;
}	t_philo;

int			main(int argc, char **argv);
void		create_threads(t_philo *p, t_sim *sim);
uint64_t	timestamp(void);
void		ft_error(char *str);

#endif