/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:55:40 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/05/01 14:42:43 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
#include "utils_actions.h"
#include "actions.h"
#include <sys/wait.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

static void	*wait_until_die(void *block)
{
	struct s_table	*thread;
	int				_;

	thread = (struct s_table *)block;
	sem_wait(thread->starved_together);
	_ = -1;
	while (++_ < thread->n_philosophers)
		if (thread->pids[_] != 0)
			kill(thread->pids[_], SIGKILL);
	return (NULL);
}

static void	wait_all_eat(struct s_table *table)
{
	int	_;
	int	ext;

	_ = -1;
	while (++_ < table->n_philosophers)
		waitpid(table->pids[_], &ext, 0);
}

static int	init_thread_monitoring(struct s_table **table)
{
	pthread_t		monitoring;

	if (pthread_create(&monitoring, NULL, wait_until_die, *table))
	{
		write(STDERR_FILENO, "Error on thread create!\n", 25);
		return (1);
	}
	pthread_detach(monitoring);
	return (0);
}

int	dont_starved_together(struct s_table *table, char *n_eat)
{
	int	_;

	_ = -1;
	while (++_ < table->n_philosophers)
	{
		table->pids[_] = fork();
		if (!table->pids[_])
		{
			table->philosopher = init_philosopher(_ + 1, n_eat);
			table->philosopher->start_sim = get_current_time();
			table->philosopher->last_meal = table->philosopher->start_sim;
			while (1)
			{
				sem_wait(table->your_time);
				get_forks(table);
				start_eat(table);
				start_sleep(table);
				start_think(table);
			}
		}
	}
	if (init_thread_monitoring(&table))
		return (1);
	wait_all_eat(table);
	return (0);
}
