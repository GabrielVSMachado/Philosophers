/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:08:38 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/21 18:37:50 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "philo.h"

void	start_think(t_mls *thinking, int seat);
void	start_eat(t_philo *philosophers);
void	start_sleep(t_philo *philosophers);
int		get_forks(t_philo *philosophers);
void	*die(int seat, t_mls thinking);
#endif
