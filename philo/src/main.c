/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:25:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/23 21:15:32 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

static void	end_dinner(t_philo **philosophers)
{
	int	_;

	_ = -1;
	while (++_ < (*philosophers)->table->n_philophers)
		pthread_mutex_destroy(&(*philosophers)->table->forks[_]);
	pthread_mutex_destroy(&(*philosophers)->table->printlock);
	free((*philosophers)->table->forks);
	(*philosophers)->table->forks = NULL;
	free((*philosophers)->table->semaphoro);
	(*philosophers)->table->semaphoro = NULL;
	free((*philosophers)->table);
	(*philosophers)->table = NULL;
	free((*philosophers));
	*philosophers = NULL;
}

static int	wait_threads(t_philo *philosophers)
{
	int	_;

	_ = -1;
	while (++_ < philosophers->table->n_philophers)
	{
		if (pthread_join(philosophers[_].philo, NULL))
		{
			write(STDERR_FILENO, "Error on joined threads\n", 25);
			return (1);
		}
	}
	return (0);
}

static int	init_threads(t_philo *philosophers)
{
	int	_;

	_ = -1;
	while (++_ < philosophers->table->n_philophers)
	{
		if (pthread_create(&(philosophers[_].philo), NULL, dont_starve_together,
				&philosophers[_]))
		{
			write(STDERR_FILENO, "Error on initialize threads\n", 29);
			return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	*philosophers;

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
	philosophers = init_table(ft_atoi(argv[1]), argv);
	if (!philosophers)
	{
		write(STDERR_FILENO, "Failed to alloc memory\n", 24);
		return (1);
	}
	init_threads(philosophers);
	wait_threads(philosophers);
	end_dinner(&philosophers);
	return (0);
}
