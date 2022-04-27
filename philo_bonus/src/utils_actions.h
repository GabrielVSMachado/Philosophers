/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:42:55 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/27 18:15:02 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_ACTIONS_H
# define UTILS_ACTIONS_H

# include "philo_bonus.h"

t_mls			get_current_time(void);
int				must_die(t_mls last_meal, t_mls die);
int				ft_atoi(const char *str);
void			destroy_table(struct s_table **table);
t_philo			*init_philosopher(int n_seat, char *argv_n_eat);
struct s_table	*init_table(int n_philosophers, char *const *argv);
void			print_msg(struct s_table *table, char *msg);
#endif
