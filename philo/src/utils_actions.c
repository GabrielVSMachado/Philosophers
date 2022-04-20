/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:04:25 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/20 17:33:08 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

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
