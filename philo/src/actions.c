/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:09:16 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/20 18:47:58 by gvitor-s         ###   ########.fr       */
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
	{
		usleep(table->die - table->philosophers->thinking);
		return (1);
	}
	get_fork_in_position(table->forks, right, table->philosophers->seat);
	return (0);
}

void	start_eat(struct s_table *table)
{
	static pthread_mutex_t	_ = PTHREAD_MUTEX_INITIALIZER;
	int						left;
	int						right;

	table->philosophers->thinking = 0;
	left = table->philosophers->seat - 2;
	left += (left < 0) * table->n_philophers;
	right = table->philosophers->seat - 1;
	printf("%d %d is eating\n", get_current_time(), table->philosophers->seat);
	usleep(table->eat);
	leave_fork(table->forks, left);
	leave_fork(table->forks, right);
	pthread_mutex_lock(&_);
	table->odd_time[
		(table->philosophers->seat - 1) % (table->n_philophers / 2)
	] = !(table->philosophers->seat % 2);
	pthread_mutex_unlock(&_);
}

void	start_sleep(struct s_table *table)
{
	printf("%d %d is sleeping\n", get_current_time(),
		table->philosophers->seat);
	usleep(table->sleep);
}
