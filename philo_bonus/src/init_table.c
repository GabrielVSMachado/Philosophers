/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:40:32 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/26 15:26:58 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_actions.h"
#include "philo_bonus.h"
#include <stdlib.h>
#include <fcntl.h>

t_philo	*init_philosopher(int n_seat, char *argv_n_eat)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->n_eat = -1;
	if (argv_n_eat)
		philo->n_eat = ft_atoi(argv_n_eat);
	philo->start_sim = 0;
	philo->last_meal = 0;
	philo->seat = n_seat;
	return (philo);
}

void	destroy_table(struct s_table **table)
{
	free((*table)->pids);
	sem_destroy((*table)->forks);
	(*table)->forks = NULL;
	sem_destroy((*table)->print);
	(*table)->print = NULL;
	sem_destroy((*table)->starved_together);
	(*table)->starved_together = NULL;
	free((*table)->philosopher);
	(*table)->philosopher = NULL;
	free((*table));
	(*table) = NULL;
}

static void	init_sem(sem_t **forks, sem_t **print, sem_t **starved_together,
		int n_philosophers)
{
	(*forks) = sem_open("forks", O_CREAT,
			S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP, n_philosophers);
	(*print) = sem_open("print", O_CREAT,
			S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP, 1);
	(*starved_together) = sem_open("print", O_CREAT,
			S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP, 0);
}

struct s_table	*init_table(unsigned long n_philosophers, char *const *argv)
{
	struct s_table	*table;

	table = malloc(sizeof(struct s_table));
	if (!table)
		return (NULL);
	table->philosopher = NULL;
	table->pids = malloc(sizeof(pid_t) * n_philosophers);
	if (!table->pids)
	{
		free(table);
		return (NULL);
	}
	init_sem(&table->forks, &table->print, &table->starved_together,
		n_philosophers);
	if (table->print == SEM_FAILED || table->forks == SEM_FAILED
		|| table->starved_together == SEM_FAILED)
	{
		destroy_table(&table);
		return (NULL);
	}
	table->philosopher = NULL;
	table->die = ft_atoi(argv[2]);
	table->eat = ft_atoi(argv[3]);
	table->sleep = ft_atoi(argv[4]);
	return (table);
}
