/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:42:55 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/26 15:30:18 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_ACTIONS_H
# define UTILS_ACTIONS_H

# include "philo_bonus.h"

int				ft_atoi(const char *str);
void			destroy_table(struct s_table **table);
t_philo			*init_philosopher(int n_seat, char *argv_n_eat);
struct s_table	*init_table(unsigned long n_philosophers, char *const *argv);
#endif
