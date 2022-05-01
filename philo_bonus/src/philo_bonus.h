/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:23:26 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/30 21:34:19 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <semaphore.h>

typedef unsigned long	t_mls;
typedef struct s_table	t_table;

typedef struct s_philo
{
	int		seat;
	int		n_eat;
	t_mls	last_meal;
	t_mls	start_sim;
}	t_philo;

struct s_table
{
	t_mls	die;
	t_mls	eat;
	t_mls	sleep;
	pid_t	*pids;
	sem_t	*starved_together;
	sem_t	*forks;
	sem_t	*print;
	sem_t	*your_time;
	t_philo	*philosopher;
	int		n_philosophers;
};

int	check_inputs(char *const *argv);
int	dont_starved_together(struct s_table *table, char *n_eat);
#endif
