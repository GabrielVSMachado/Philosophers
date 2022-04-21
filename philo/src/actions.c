/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:09:16 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/21 18:38:04 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_actions.h"
#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	start_think(t_mls *thinking, int seat)
{
	*thinking = get_current_time();
	printf("%lu %d is thinking\n", get_current_time() - *thinking, seat);
}

int	get_forks(t_philo *philosophers)
{
	static pthread_mutex_t	_ = PTHREAD_MUTEX_INITIALIZER;
	int						left;
	int						right;

	left = philosophers->seat - 2;
	left += (left < 0) * philosophers->table->n_philophers;
	right = philosophers->seat - 1;
	get_fork_in_position(philosophers->table->forks, left, philosophers->seat,
		philosophers->thinking);
	if (left == right)
		usleep(1000 * (philosophers->table->die
				- (get_current_time() - philosophers->thinking)));
	if (get_current_time() - philosophers->thinking >= philosophers->table->die)
		return (1);
	get_fork_in_position(philosophers->table->forks, right, philosophers->seat,
		philosophers->thinking);
	pthread_mutex_lock(&_);
	philosophers->table->odd_time[
		(philosophers->seat - 1) % (philosophers->table->n_philophers / 2)
	] = !(philosophers->seat % 2);
	pthread_mutex_unlock(&_);
	return (0);
}

void	start_eat(t_philo *philosophers)
{
	int						left;
	int						right;

	philosophers->thinking = 0;
	left = philosophers->seat - 2;
	left += (left < 0) * philosophers->table->n_philophers;
	right = philosophers->seat - 1;
	printf("%ld %d is eating\n", get_current_time() - philosophers->thinking,
		philosophers->seat);
	usleep(philosophers->table->eat * 1000);
	leave_fork(philosophers->table->forks, left);
	leave_fork(philosophers->table->forks, right);
}

void	start_sleep(t_philo *philosophers)
{
	printf("%ld %d is sleeping\n", get_current_time() - philosophers->thinking,
		philosophers->seat);
	usleep(philosophers->table->sleep * 1000);
}

void	*die(int seat, t_mls thinking)
{
	void	*die;

	die = malloc(sizeof(int));
	printf("%ld %d died\n", get_current_time() - thinking, seat);
	*(int *)die = 1;
	return (die);
}
