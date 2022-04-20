/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:08:38 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/20 19:59:49 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "philo.h"

void	start_think(t_time *thinking, int seat);
void	start_eat(struct s_table *table);
void	start_sleep(struct s_table *table);
int		get_forks(struct s_table *table);
void	*die(int seat);
#endif
