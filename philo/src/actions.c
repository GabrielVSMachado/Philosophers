/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:09:16 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/23 21:42:28 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_actions.h"
#include "philo.h"
#include <stdio.h>
#include <stdlib.h>

void	start_think(t_mls *thinking, int seat, struct s_table *table)
{
	pthread_mutex_lock(&table->printlock);
	if (table->starved_together)
	{
		pthread_mutex_unlock(&table->printlock);
		pthread_exit(NULL);
	}
	*thinking = get_current_time();
	printf("%lu %d is thinking\n", get_current_time() - *thinking, seat);
	pthread_mutex_unlock(&table->printlock);
}

int	get_forks(t_philo *philosophers)
{
	int						left;
	int						right;

	left = philosophers->seat - 2;
	left += (left < 0) * philosophers->table->n_philophers;
	right = philosophers->seat - 1;
	get_fork_in_position(philosophers->table, left, philosophers->seat,
		philosophers->thinking);
	if (left == right)
		usleep(1000 * (philosophers->table->die
				- (get_current_time() - philosophers->thinking)));
	if (get_current_time() - philosophers->thinking >= philosophers->table->die)
		return (1);
	get_fork_in_position(philosophers->table, right, philosophers->seat,
		philosophers->thinking);
	return (0);
}

void	start_eat(t_philo *philosophers)
{
	int						left;
	int						right;
	int						seat;
	int						n_philophers;

	seat = philosophers->seat;
	n_philophers = philosophers->table->n_philophers;
	left = seat - 2;
	left += (left < 0) * philosophers->table->n_philophers;
	right = seat - 1;
	pthread_mutex_lock(&philosophers->table->printlock);
	printf("%ld %d is eating\n",
		get_current_time() - philosophers->thinking, seat);
	pthread_mutex_unlock(&philosophers->table->printlock);
	usleep(philosophers->table->eat * 1000);
	leave_fork(philosophers->table->forks, left);
	leave_fork(philosophers->table->forks, right);
	pthread_mutex_lock(&philosophers->table->printlock);
	philosophers->table->semaphoro[seat - 1].smp = 0;
	philosophers->table->semaphoro[seat % n_philophers].smp = 1;
	if (philosophers->table->starved_together)
		return (pthread_mutex_unlock(&philosophers->table->printlock),
			pthread_exit(NULL));
	pthread_mutex_unlock(&philosophers->table->printlock);
}

void	start_sleep(t_philo *philosophers)
{
	pthread_mutex_lock(&philosophers->table->printlock);
	printf("%ld %d is sleeping\n", get_current_time() - philosophers->thinking,
		philosophers->seat);
	pthread_mutex_unlock(&philosophers->table->printlock);
	usleep(philosophers->table->sleep * 1000);
	pthread_mutex_lock(&philosophers->table->printlock);
	if (philosophers->table->starved_together)
	{
		pthread_mutex_unlock(&philosophers->table->printlock);
		pthread_exit(NULL);
	}
	pthread_mutex_unlock(&philosophers->table->printlock);
}

void	die(t_philo *philosophers)
{
	pthread_mutex_lock(&philosophers->table->printlock);
	if (!philosophers->table->starved_together)
	{
		philosophers->table->starved_together = 1;
		printf("%ld %d died\n",
			get_current_time() - philosophers->thinking,
			philosophers->seat);
	}
	pthread_mutex_unlock(&philosophers->table->printlock);
	pthread_exit(NULL);
}
