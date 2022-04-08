/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:22:23 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/07 22:41:28 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>

void	destroy_table(struct s_table **table)
{
	while ((*table)->n_philophers--)
		pthread_mutex_destroy(&(*table)->forks[(*table)->n_philophers]);
	free((*table)->philosophers);
	free((*table)->forks);
	free(*table);
	*table = NULL;
}

static pthread_mutex_t	*init_mutex(int n_philophers)
{
	pthread_mutex_t	*mtx;
	int				m_pos;

	mtx = malloc(sizeof(pthread_mutex_t) * n_philophers + 1);
	if (!mtx)
		return (NULL);
	m_pos = -1;
	while (++m_pos < n_philophers)
		pthread_mutex_init(&mtx[m_pos], NULL);
	return (mtx);
}

static t_philo	*init_philosophers(struct s_table *table, int n_philophers,
		char *argv[])
{
	t_philo	*philo;
	t_eat	n_eat;
	int		_;

	philo = malloc(sizeof(t_philo) * n_philophers);
	if (!philo)
	{
		_ = -1;
		while (++_ < n_philophers)
			pthread_mutex_destroy(&table->forks[_]);
		free(table->forks);
		return (NULL);
	}
	_ = -1;
	n_eat = 0;
	if (argv[5])
		n_eat = ft_atoi(argv[5]);
	while (++_ < n_philophers)
	{
		philo[_].dead = 0;
		philo[_].start_think = 0;
		philo[_].n_eat = n_eat;
	}
	return (philo);
}

struct s_table	*init_table(int n_philophers, char *argv[])
{
	struct s_table	*table;

	table = malloc(sizeof(struct s_table));
	if (!table)
		return (NULL);
	table->forks = init_mutex(n_philophers);
	if (!table->forks)
	{
		free(table);
		return (NULL);
	}
	table->philosophers = init_philosophers(table, n_philophers, argv);
	if (!table->philosophers)
	{
		free(table);
		return (NULL);
	}
	table->n_philophers = n_philophers;
	table->die = ft_atoi(argv[2]);
	table->eat = ft_atoi(argv[3]);
	table->sleep = ft_atoi(argv[4]);
	return (table);
}
