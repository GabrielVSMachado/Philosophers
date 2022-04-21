/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 20:22:23 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/21 17:18:26 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void	end_dinner(t_philo **philosophers)
{
	int	_;

	_ = -1;
	while (++_ < (*philosophers)->table->n_philophers)
		pthread_mutex_destroy(&(*philosophers)->table->forks[_]);
	free((*philosophers)->table->forks);
	(*philosophers)->table->forks = NULL;
	free((*philosophers)->table->odd_time);
	(*philosophers)->table->odd_time = NULL;
	free((*philosophers)->table);
	(*philosophers)->table = NULL;
	free((*philosophers));
	*philosophers = NULL;
}

static pthread_mutex_t	*init_mutex(int n_philophers)
{
	pthread_mutex_t	*mtx;
	int				_;

	mtx = malloc(sizeof(pthread_mutex_t) * n_philophers);
	if (!mtx)
		return (NULL);
	_ = -1;
	while (++_ < n_philophers)
		pthread_mutex_init(&mtx[_], NULL);
	return (mtx);
}

static t_philo	*init_philosophers(char *argv[], int n_philophers,
		struct s_table *table)
{
	t_philo	*philosophers;
	int		_;
	int		n_eat;

	philosophers = malloc(sizeof(struct s_philo) * n_philophers);
	if (!philosophers)
		return (NULL);
	n_eat = 0;
	if (argv[5])
		n_eat = ft_atoi(argv[5]);
	_ = -1;
	while (++_ < n_philophers)
	{
		philosophers[_].philo = 0;
		philosophers[_].seat = _ + 1;
		philosophers[_].thinking = 0;
		philosophers[_].table = table;
		philosophers[_].n_eat = n_eat;
	}
	return (philosophers);
}

static struct s_table	*prepare_table(int n_philophers, char *argv[])
{
	struct s_table	*table;

	table = malloc(sizeof(struct s_table));
	if (!table)
		return (NULL);
	table->odd_time = memset(malloc(sizeof(int) * n_philophers / 2), 1,
			sizeof(int) * (n_philophers / 2));
	if (!table->odd_time)
	{
		free(table);
		return (NULL);
	}
	table->forks = init_mutex(n_philophers);
	if (!table->forks)
	{
		free(table->odd_time);
		free(table);
		return (NULL);
	}
	table->n_philophers = n_philophers;
	table->die = ft_atoi(argv[2]);
	table->eat = ft_atoi(argv[3]);
	table->sleep = ft_atoi(argv[4]);
	return (table);
}

t_philo	*init_table(int n_philophers, char *argv[])
{
	t_philo			*philosophers;
	struct s_table	*table;

	table = prepare_table(n_philophers, argv);
	if (!table)
		return (NULL);
	philosophers = init_philosophers(argv, n_philophers, table);
	if (!philosophers)
	{
		free(table);
		return (NULL);
	}
	return (philosophers);
}
