/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:01:14 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/30 19:25:40 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>

typedef unsigned long	t_mls;
typedef unsigned long	t_eat;

typedef struct s_waiter
{
	unsigned int	smp:1;
}	t_waiter;

struct s_table
{
	int				n_philophers;
	pthread_mutex_t	*forks;
	pthread_mutex_t	printlock;
	pthread_mutex_t	check_your_time;
	pthread_mutex_t	check_is_dead;
	t_waiter		*semaphoro;
	t_mls			eat;
	t_mls			sleep;
	t_mls			die;
	unsigned int	starved_together:1;
};

typedef struct s_philo
{
	int				seat;
	pthread_t		philo;
	t_mls			start_sim;
	t_mls			last_meal;
	t_eat			n_eat;
	unsigned int	thinking:1;
	struct s_table	*table;
}	t_philo;

int		check_inputs(char **argv);
int		ft_atoi(const char *str);
t_philo	*init_table(int n_philophers, char *argv[]);
void	*dont_starve_together(void *block);
#endif
