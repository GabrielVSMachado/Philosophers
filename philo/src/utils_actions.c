/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:04:25 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/21 18:40:48 by gvitor-s         ###   ########.fr       */
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

int	wait_until_odd_end(t_philo *philosophers)
{
	static pthread_mutex_t	_ = PTHREAD_MUTEX_INITIALIZER;
	int						n_phls;
	int						seat;
	int						*odd_time;
	int						access;

	seat = philosophers->seat;
	n_phls = philosophers->table->n_philophers;
	odd_time = philosophers->table->odd_time;
	access = (int)(n_phls / 2);
	access += (!access);
	while (pthread_mutex_lock(&_), odd_time[(seat - 1) % access])
	{
		pthread_mutex_unlock(&_);
		if (get_current_time() - philosophers->thinking
			>= philosophers->table->die)
			return (1);
	}
	return (0);
}

int	wait_until_even_end(t_philo *philosophers)
{
	static pthread_mutex_t	_ = PTHREAD_MUTEX_INITIALIZER;
	int						n_phls;
	int						seat;
	int						*odd_time;
	int						access;

	seat = philosophers->seat;
	n_phls = philosophers->table->n_philophers;
	odd_time = philosophers->table->odd_time;
	access = (int)(n_phls / 2);
	access += (!access);
	while (pthread_mutex_lock(&_), !odd_time[(seat - 1) % access])
	{
		pthread_mutex_unlock(&_);
		if (get_current_time() - philosophers->thinking
			>= philosophers->table->die)
			return (1);
	}
	return (0);
}
