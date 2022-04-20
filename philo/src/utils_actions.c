/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:04:25 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/20 19:54:43 by gvitor-s         ###   ########.fr       */
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

	gettimeofday(&tv, NULL);
	return (tv.tv_sec / 1000);
}

void	get_fork_in_position(pthread_mutex_t *forks, int position, int seat)
{
	pthread_mutex_lock(&forks[position]);
	printf("%d %d has taken a fork\n", get_current_time(), seat);
}

void	leave_fork(pthread_mutex_t *forks, int position)
{
	pthread_mutex_unlock(&forks[position]);
}

int	wait_until_odd_end(struct s_table *table)
{
	static pthread_mutex_t	_ = PTHREAD_MUTEX_INITIALIZER;
	int						n_phls;
	int						seat;

	seat = table->philosophers->seat;
	n_phls = table->n_philophers;
	while (pthread_mutex_lock(&_), table->odd_time[(seat - 1) % (n_phls / 2)])
	{
		pthread_mutex_unlock(&_);
		if (get_current_time() - table->philosophers->thinking >= table->die)
			return (1);
	}
	return (0);
}

int	wait_until_even_end(struct s_table *table)
{
	static pthread_mutex_t	_ = PTHREAD_MUTEX_INITIALIZER;
	int						n_phls;
	int						seat;

	seat = table->philosophers->seat;
	n_phls = table->n_philophers;
	while (pthread_mutex_lock(&_), !table->odd_time[(seat - 1) % (n_phls / 2)])
	{
		pthread_mutex_unlock(&_);
		if (get_current_time() - table->philosophers->thinking >= table->die)
			return (1);
	}
	return (0);
}
