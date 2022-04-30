/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:04:25 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/30 19:08:40 by gvitor-s         ###   ########.fr       */
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

void	print_msg(char *msg, t_philo *philosopher)
{
	pthread_mutex_lock(&philosopher->table->printlock);
	printf(msg, get_current_time() - philosopher->start_sim,
		philosopher->seat);
	pthread_mutex_unlock(&philosopher->table->printlock);
}

void	get_fork_in_position(t_philo *philosophers, int position)
{
	pthread_mutex_lock(&philosophers->table->forks[position]);
}

void	leave_fork(pthread_mutex_t *forks, int position)
{
	pthread_mutex_unlock(&forks[position]);
}

void	change_semaphoros(struct s_table *table, int seat)
{
	pthread_mutex_lock(&table->check_your_time);
	table->semaphoro[seat - 1].smp = 0;
	table->semaphoro[seat % table->n_philophers].smp = 1;
	pthread_mutex_unlock(&table->check_your_time);
}
