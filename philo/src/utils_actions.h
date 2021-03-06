/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:07:22 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/30 20:38:43 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_ACTIONS_H
# define UTILS_ACTIONS_H

# include <pthread.h>
# include "philo.h"

void	make_action(t_philo *philosopher, t_mls time_action);
t_mls	get_current_time(void);
void	leave_fork(pthread_mutex_t *forks, int position);
void	get_fork_in_position(t_philo *philosophers, int fstposition,
			int secposition);
void	wait_until_its_time(t_philo *philosophers);
void	change_semaphoros(struct s_table *table, int seat);
int		cant_eat_anymore(t_philo *philosophers);
int		must_die(t_philo *philosopher);
void	print_msg(char *msg, t_philo *philosopher);
#endif
