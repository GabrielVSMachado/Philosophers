/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:25:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/20 20:04:43 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

static void	wait_threads(struct s_table **table)
{
	int	_;
	int	*dead;

	_ = -1;
	dead = NULL;
	while (++_ < (*table)->n_philophers)
	{
		if (pthread_join((*table)->philosophers[_].philo, (void **)&dead))
		{
			write(STDERR_FILENO, "Error in wait threads\n", 23);
			destroy_table(table);
			exit(EXIT_FAILURE);
		}
		if (dead && *dead)
		{
			free(dead);
			destroy_table(table);
			exit(EXIT_FAILURE);
		}
	}
	destroy_table(table);
	exit(EXIT_SUCCESS);
}

static void	init_threads(struct s_table **table)
{
	int		_;
	t_philo	*cerimony_master;

	_ = 0;
	cerimony_master = (*table)->philosophers;
	while (_ < (*table)->n_philophers)
	{
		if (pthread_create(&(*table)->philosophers->philo, NULL,
				start_dinner, table))
		{
			(*table)->philosophers = cerimony_master;
			destroy_table(table);
			write(STDERR_FILENO, "Error on create threads\n", 25);
			exit(EXIT_FAILURE);
		}
		(*table)->philosophers = &(*table)->philosophers[++_];
	}
	(*table)->philosophers = cerimony_master;
}

int	main(int argc, char **argv)
{
	struct s_table	*table;

	if (argc < 4)
	{
		write(STDERR_FILENO, "Too few arguments!\n", 20);
		return (1);
	}
	if (check_inputs(argv))
	{
		write(STDERR_FILENO, "Invalid argument passed!\n", 20);
		return (1);
	}
	table = init_table(ft_atoi(argv[1]), argv);
	if (!table)
	{
		write(STDERR_FILENO, "Failed to alloc memory\n", 24);
		return (1);
	}
	init_threads(&table);
	wait_threads(&table);
}
