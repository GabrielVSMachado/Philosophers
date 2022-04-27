/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:11:01 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/27 13:07:47 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_actions.h"
#include <semaphore.h>
#include <stdlib.h>

void	die(struct s_table **table)
{
	sem_post((*table)->starved_together);
	print_msg((*table), "%ld %d die\n");
	destroy_table(table);
	exit(EXIT_FAILURE);
}

void	start_think(struct s_table *table)
{
	print_msg(table, "%ld %d is thinking\n");
}

void	get_forks(struct s_table *table)
{
	sem_wait(table->forks);
	print_msg(table, "%ld %d has taken a fork\n");
	sem_wait(table->forks);
	print_msg(table, "%ld %d has taken a fork\n");
}

void	start_eat(struct s_table *table)
{
	table->philosopher->last_meal = get_current_time();
	print_msg(table, "%ld %d is eating\n");
	usleep(table->eat * 1000);
	sem_post(table->forks);
	sem_post(table->forks);
}

void	start_sleep(struct s_table *table)
{
	print_msg(table, "%ld %d is sleeping\n");
	usleep(table->sleep * 1000);
}
