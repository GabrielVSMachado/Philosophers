/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:09:16 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/22 17:56:01 by gvitor-s         ###   ########.fr       */
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
	return (0);
}

void	start_eat(t_philo *philosophers)
{
	int						left;
	int						right;
	int						seat;
	int						n_philophers;
	static pthread_mutex_t	_ = PTHREAD_MUTEX_INITIALIZER;

	seat = philosophers->seat;
	n_philophers = philosophers->table->n_philophers;
	left = seat - 2;
	left += (left < 0) * philosophers->table->n_philophers;
	right = seat - 1;
	printf("%ld %d is eating\n",
		get_current_time() - philosophers->thinking, seat);
	usleep(philosophers->table->eat * 1000);
	leave_fork(philosophers->table->forks, left);
	leave_fork(philosophers->table->forks, right);
	pthread_mutex_lock(&_);
	philosophers->table->semaphoro[seat - 1].smp = 0;
	philosophers->table->semaphoro[seat % n_philophers].smp = 1;
	pthread_mutex_unlock(&_);
}

void	start_sleep(t_philo *philosophers)
{
	printf("%ld %d is sleeping\n", get_current_time() - philosophers->thinking,
		philosophers->seat);
	usleep(philosophers->table->sleep * 1000);
}

void	*die(int seat, t_mls thinking, t_death *starved_together)
{
	void					*die;
	static pthread_mutex_t	_ = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&_);
	*starved_together = 1;
	pthread_mutex_unlock(&_);
	die = malloc(sizeof(int));
	printf("%ld %d died\n", get_current_time() - thinking, seat);
	*(int *)die = 1;
	return (die);
}
