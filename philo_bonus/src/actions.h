/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:17:56 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/27 13:53:53 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "philo_bonus.h"

void	start_think(struct s_table *table);
void	die(struct s_table **table);
void	get_forks(struct s_table *table);
void	start_eat(struct s_table *table);
void	start_sleep(struct s_table *table);
#endif
