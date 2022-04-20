/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:01:14 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/20 16:39:51 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>

typedef unsigned long	t_death;
typedef unsigned long	t_time;
typedef unsigned long	t_eat;

typedef struct s_philo
{
	int			seat;
	pthread_t	philo;
	t_time		thinking;
	t_eat		n_eat;
}	t_philo;

struct s_table
{
	t_philo			*philosophers;
	int				n_philophers;
	pthread_mutex_t	*forks;
	t_time			eat;
	useconds_t		sleep;
	t_time			die;
};

int				check_inputs(char **argv);
int				ft_atoi(const char *str);
struct s_table	*init_table(int n_philophers, char *argv[]);
void			destroy_table(struct s_table **table);
#endif
