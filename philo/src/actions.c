/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:09:16 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/20 16:36:27 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_actions.h"
#include "philo.h"
#include <stdio.h>

void	start_think(t_time *thinking, int seat)
{
	*thinking = get_current_time();
	printf("%lu %d is thinking\n", *thinking, seat);
}

int	get_forks(struct s_table *table)
{
	int	left;
	int	right;

	left = table->philosophers->seat - 2;
	left += (left < 0) * table->n_philophers;
	right = table->philosophers->seat - 1;
	get_fork_in_position(table->forks, left, table->philosophers->seat);
	if (left == right)
		usleep(table->die - table->philosophers->thinking);
	if (get_current_time() - table->philosophers->thinking >= table->die)
		return (1);
	get_fork_in_position(table->forks, right, table->philosophers->seat);
	return (0);
}
