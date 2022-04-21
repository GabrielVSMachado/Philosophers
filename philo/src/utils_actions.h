/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:07:22 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/21 18:11:15 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_ACTIONS_H
# define UTILS_ACTIONS_H

# include <pthread.h>
# include "philo.h"

int		get_current_time(void);
void	leave_fork(pthread_mutex_t *forks, int position);
void	get_fork_in_position(pthread_mutex_t *forks, int position, int seat,
			int thinking);
int		wait_until_odd_end(t_philo *philosophers);
int		wait_until_even_end(t_philo *philosophers);
#endif
