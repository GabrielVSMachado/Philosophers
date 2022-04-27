/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 11:11:01 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/27 19:19:57 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_actions.h"
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>

void	die(struct s_table **table)
{
	sem_wait((*table)->print);
	printf("%ld %d die\n",
		get_current_time() - (*table)->philosopher->start_sim,
		(*table)->philosopher->seat);
	sem_post((*table)->starved_together);
	while (1)
		;
}

void	start_think(struct s_table *table)
{
	print_msg(table, "%ld %d is thinking\n");
}

void	get_forks(struct s_table *table)
{
	sem_wait(table->forks);
	print_msg(table, "%ld %d has taken a fork\n");
	if (table->n_philosophers == 1)
	{
		usleep(table->die * 1000);
		die(&table);
	}
	sem_wait(table->forks);
	print_msg(table, "%ld %d has taken a fork\n");
	if (must_die(table->philosopher->last_meal, table->die))
		die(&table);
}

void	start_eat(struct s_table *table)
{
	table->philosopher->last_meal = get_current_time();
	print_msg(table, "%ld %d is eating\n");
	usleep(table->eat * 1000);
	sem_post(table->forks);
	sem_post(table->forks);
	sem_post(table->your_time);
	table->philosopher->n_eat -= (table->philosopher->n_eat > 0);
	if (table->philosopher->n_eat == 0)
	{
		destroy_table(&table);
		exit(EXIT_SUCCESS);
	}
	if (must_die(table->philosopher->last_meal, table->die))
		die(&table);
}

void	start_sleep(struct s_table *table)
{
	print_msg(table, "%ld %d is sleeping\n");
	usleep(table->sleep * 1000);
	if (must_die(table->philosopher->last_meal, table->die))
		die(&table);
}
