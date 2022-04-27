/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:11:39 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/27 18:00:44 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo_bonus.h"
#include <stdio.h>

t_mls	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	must_die(t_mls last_meal, t_mls die)
{
	return (get_current_time() - last_meal >= die);
}

void	print_msg(struct s_table *table, char *msg)
{
	sem_wait(table->print);
	printf(msg, get_current_time() - table->philosopher->start_sim,
		table->philosopher->seat);
	sem_post(table->print);
}
