/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:01:14 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/28 23:15:31 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>

typedef unsigned long	t_death;
typedef unsigned long	t_mls;
typedef unsigned long	t_eat;

typedef struct s_semaphoro
{
	unsigned int	smp:1;
}	t_semaphoro;

struct s_table
{
	int				n_philophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printlock;
	t_semaphoro		*semaphoro;
	t_mls			eat;
	t_mls			sleep;
	t_mls			die;
	_Atomic t_death	starved_together;
};

typedef struct s_philo
{
	int				seat;
	pthread_t		philo;
	t_mls			start_sim;
	t_mls			last_meal;
	t_eat			n_eat;
	struct s_table	*table;
}	t_philo;

int				check_inputs(char **argv);
int				ft_atoi(const char *str);
t_philo			*init_table(int n_philophers, char *argv[]);
void			*dont_starve_together(void *block);
#endif
