/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:09:16 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/30 19:30:00 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_actions.h"
#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	die(t_philo *philosophers)
{
	pthread_mutex_lock(&philosophers->table->check_is_dead);
	if (!philosophers->table->starved_together)
	{
		philosophers->table->starved_together = 1;
		print_msg("%ld %d die\n", philosophers);
	}
	pthread_mutex_unlock(&philosophers->table->check_is_dead);
	pthread_exit(NULL);
}

void	start_think(t_philo *philosophers)
{
	philosophers->thinking = 1;
	print_msg("%ld %d is thinking\n", philosophers);
	if (must_die(philosophers))
		die(philosophers);
}

void	get_forks(t_philo *philosophers)
{
	int	left;
	int	right;

	left = philosophers->seat - 2;
	left += (left < 0) * philosophers->table->n_philophers;
	right = philosophers->seat - 1;
	if (left == right)
	{
		get_fork_in_position(philosophers, left);
		leave_fork(philosophers->table->forks, left);
		usleep(philosophers->table->die * 1000);
		die(philosophers);
	}
	get_fork_in_position(philosophers, left);
	print_msg("%ld %d has taken a fork\n", philosophers);
	get_fork_in_position(philosophers, right);
	print_msg("%ld %d has taken a fork\n", philosophers);
	if (must_die(philosophers))
	{
		leave_fork(philosophers->table->forks, left);
		leave_fork(philosophers->table->forks, right);
		die(philosophers);
	}
}

void	start_eat(t_philo *philosophers)
{
	int	left;
	int	right;
	int	seat;

	philosophers->last_meal = get_current_time();
	seat = philosophers->seat;
	left = seat - 2;
	left += (left < 0) * philosophers->table->n_philophers;
	right = seat - 1;
	philosophers->thinking = 0;
	print_msg("%ld %d is eating\n", philosophers);
	leave_fork(philosophers->table->forks, left);
	leave_fork(philosophers->table->forks, right);
	make_action(philosophers, philosophers->table->eat);
	if (must_die(philosophers))
		die(philosophers);
	change_semaphoros(philosophers->table, philosophers->seat);
	philosophers->n_eat -= (philosophers->n_eat > 0);
	if (cant_eat_anymore(philosophers))
		pthread_exit(NULL);
}

void	start_sleep(t_philo *philosophers)
{
	print_msg("%ld %d is sleeping\n", philosophers);
	make_action(philosophers, philosophers->table->sleep);
	if (must_die(philosophers))
		die(philosophers);
}
