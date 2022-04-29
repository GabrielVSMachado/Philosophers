/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:04:25 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/29 21:09:46 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "philo.h"
#include "actions.h"
#include "utils_actions.h"

t_mls	get_current_time(void)
{
	struct timeval	tv;
	t_mls			mls_time;

	gettimeofday(&tv, NULL);
	mls_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (mls_time);
}

void	get_fork_in_position(t_philo *philosophers, int position)
{
	pthread_mutex_lock(&philosophers->table->printlock);
	printf("%ld %d has taken a fork\n",
		get_current_time() - philosophers->start_sim,
		philosophers->seat);
	pthread_mutex_unlock(&philosophers->table->printlock);
	pthread_mutex_lock(&philosophers->table->forks[position]);
}

void	leave_fork(pthread_mutex_t *forks, int position)
{
	pthread_mutex_unlock(&forks[position]);
}

void	wait_until_its_time(t_philo *philosophers)
{
	t_semaphoro	*time;
	int			its_your_time;

	time = philosophers->table->semaphoro;
	pthread_mutex_lock(&philosophers->table->check_your_time);
	its_your_time = !time[philosophers->seat - 1].smp;
	pthread_mutex_unlock(&philosophers->table->check_your_time);
	while (its_your_time)
	{
		if (must_die(philosophers))
			die(philosophers);
		pthread_mutex_lock(&philosophers->table->check_your_time);
		its_your_time = !time[philosophers->seat - 1].smp;
		pthread_mutex_unlock(&philosophers->table->check_your_time);
	}
	if (must_die(philosophers))
		die(philosophers);
}

void	change_semaphoros(struct s_table *table, int seat)
{
	pthread_mutex_lock(&table->check_your_time);
	table->semaphoro[seat - 1].smp = 0;
	table->semaphoro[seat % table->n_philophers].smp = 1;
	pthread_mutex_unlock(&table->check_your_time);
}
