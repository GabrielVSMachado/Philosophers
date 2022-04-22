/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:04:25 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/22 16:53:48 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "philo.h"

int	get_current_time(void)
{
	struct timeval	tv;
	t_mls			mls_time;

	gettimeofday(&tv, NULL);
	mls_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (mls_time);
}

void	get_fork_in_position(pthread_mutex_t *forks, int position, int seat,
		t_mls thinking)
{
	pthread_mutex_lock(&forks[position]);
	printf("%ld %d has taken a fork\n", get_current_time() - thinking, seat);
}

void	leave_fork(pthread_mutex_t *forks, int position)
{
	pthread_mutex_unlock(&forks[position]);
}

int	wait_until_its_time(t_philo *philosophers)
{
	t_semaphoro				*time;

	time = philosophers->table->semaphoro;
	while (!time[philosophers->seat - 1].smp)
	{
		if (get_current_time() - philosophers->thinking
			>= philosophers->table->die)
			return (1);
	}
	return (0);
}
