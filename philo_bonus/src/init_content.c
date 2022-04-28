/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 12:40:32 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/28 17:09:31 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils_actions.h"
#include "philo_bonus.h"
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <string.h>

t_philo	*init_philosopher(int seat, char *argv_n_eat)
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
	philo->seat = seat;
	return (philo);
}

void	destroy_table(struct s_table **table)
{
	free((*table)->pids);
	sem_close((*table)->forks);
	sem_close((*table)->print);
	sem_close((*table)->your_time);
	sem_close((*table)->starved_together);
	free((*table)->philosopher);
	(*table)->philosopher = NULL;
	free((*table));
	(*table) = NULL;
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/starved_together");
	sem_unlink("/your_time");
}

static void	init_sem(struct s_table *table, int n_philosophers)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/starved_together");
	sem_unlink("/your_time");
	table->forks = sem_open("forks", O_CREAT | O_EXCL,
			S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP, n_philosophers);
	table->print = sem_open("print", O_CREAT | O_EXCL,
			S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP, 1);
	table->starved_together = sem_open("starved_together", O_CREAT | O_EXCL,
			S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP, 0);
	table->your_time = sem_open("your_time", O_CREAT | O_EXCL,
			S_IWUSR | S_IRUSR | S_IROTH | S_IRGRP, (int)(n_philosophers / 2)
			+ (n_philosophers == 1));
}

struct s_table	*init_table(int n_philosophers, char *const *argv)
{
	struct s_table	*table;

	table = malloc(sizeof(struct s_table));
	if (!table)
		return (NULL);
	table->philosopher = NULL;
	table->pids = memset(malloc(sizeof(pid_t) * n_philosophers),
			-1, sizeof(pid_t) * n_philosophers);
	if (!table->pids)
		return (free(table), NULL);
	init_sem(table, n_philosophers);
	if (table->print == SEM_FAILED || table->forks == SEM_FAILED
		|| table->starved_together == SEM_FAILED
		|| table->your_time == SEM_FAILED)
	{
		destroy_table(&table);
		return (NULL);
	}
	table->n_philosophers = n_philosophers;
	table->die = ft_atoi(argv[2]);
	table->eat = ft_atoi(argv[3]);
	table->sleep = ft_atoi(argv[4]);
	return (table);
}
