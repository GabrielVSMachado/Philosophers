/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:01:14 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/21 18:37:21 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>

typedef unsigned long	t_death;
typedef unsigned long	t_mls;
typedef unsigned long	t_eat;

struct s_table
{
	int				n_philophers;
	pthread_mutex_t	*forks;
	int				*odd_time;
	t_mls			eat;
	t_mls			sleep;
	t_mls			die;
};

typedef struct s_philo
{
	int				seat;
	pthread_t		philo;
	t_mls			thinking;
	t_eat			n_eat;
	struct s_table	*table;
}	t_philo;

int				check_inputs(char **argv);
int				ft_atoi(const char *str);
t_philo			*init_table(int n_philophers, char *argv[]);
void			end_dinner(t_philo **philophers);
void			*start_dinner(void *block);
#endif
