/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:09:16 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/24 18:02:23 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_actions.h"
#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	die(t_philo *philosophers)
{
	if (!philosophers->table->starved_together)
	{
		pthread_mutex_lock(&philosophers->table->printlock);
		philosophers->table->starved_together = 1;
		printf("%ld %d died\n", get_current_time() - philosophers->start_sim,
			philosophers->seat);
		pthread_mutex_unlock(&philosophers->table->printlock);
	}
	pthread_exit(NULL);
}

void	start_think(t_philo *philosophers)
{
	if (someone_is_starved(philosophers))
		pthread_exit(NULL);
	if (!philosophers->last_meal)
		philosophers->last_meal = get_current_time();
	pthread_mutex_lock(&philosophers->table->printlock);
	printf("%lu %d is thinking\n",
		get_current_time() - philosophers->start_sim,
		philosophers->seat);
	pthread_mutex_unlock(&philosophers->table->printlock);
}

void	get_forks(t_philo *philosophers)
{
	int						left;
	int						right;

	left = philosophers->seat - 2;
	left += (left < 0) * philosophers->table->n_philophers;
	right = philosophers->seat - 1;
	get_fork_in_position(philosophers, left);
	if (left == right)
	{
		leave_fork(philosophers->table->forks, left);
		usleep(philosophers->table->die * 1000);
		philosophers->last_meal = get_current_time() + philosophers->table->die;
	}
	if (must_die(philosophers->last_meal, philosophers->table->die)
		|| someone_is_starved(philosophers))
		die(philosophers);
	get_fork_in_position(philosophers, right);
}

void	start_eat(t_philo *philosophers)
{
	int						left;
	int						right;
	int						seat;

	seat = philosophers->seat;
	left = seat - 2;
	left += (left < 0) * philosophers->table->n_philophers;
	right = seat - 1;
	pthread_mutex_lock(&philosophers->table->printlock);
	printf("%ld %d is eating\n",
		get_current_time() - philosophers->start_sim, seat);
	pthread_mutex_unlock(&philosophers->table->printlock);
	usleep(philosophers->table->eat * 1000);
	leave_fork(philosophers->table->forks, left);
	leave_fork(philosophers->table->forks, right);
	philosophers->last_meal = get_current_time();
	philosophers->n_eat -= (philosophers->n_eat > 0);
	change_semaphoros(philosophers->table, philosophers->seat);
	if (cant_eat_anymore(philosophers))
		pthread_exit(NULL);
	if (someone_is_starved(philosophers)
		|| must_die(philosophers->last_meal, philosophers->table->die))
		die(philosophers);
}

void	start_sleep(t_philo *philosophers)
{
	pthread_mutex_lock(&philosophers->table->printlock);
	printf("%ld %d is sleeping\n", get_current_time() - philosophers->start_sim,
		philosophers->seat);
	pthread_mutex_unlock(&philosophers->table->printlock);
	usleep(philosophers->table->sleep * 1000);
	if (someone_is_starved(philosophers))
		pthread_exit(NULL);
}
