/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:55:40 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/27 19:07:39 by gvitor-s         ###   ########.fr       */
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
	struct s_thread	*thread;
	int				_;

	thread = (struct s_thread *)block;
	sem_wait(thread->starved_together);
	_ = -1;
	while (++_ < thread->n_philosophers)
		if (thread->pids[_] != -1)
			kill(thread->pids[_], SIGKILL);
	free(thread);
	return (NULL);
}

static void	wait_all_eat(struct s_table *table)
{
	int	_;
	int	ext;

	_ = -1;
	while (++_ < table->n_philosophers)
		waitpid(table->pids[_], &ext, 0);
	if (WIFEXITED(ext))
		memset(table->pids, -1, sizeof(pid_t) * table->n_philosophers);
	sem_post(table->starved_together);
}

static int	init_thread_monitoring(pid_t *pids, sem_t *starved_together,
		int n_philosophers)
{
	struct s_thread	*block;
	pthread_t		monitoring;

	block = malloc(sizeof(struct s_thread));
	if (!block)
		return (1);
	block->n_philosophers = n_philosophers;
	block->pids = pids;
	block->starved_together = starved_together;
	if (pthread_create(&monitoring, NULL, wait_until_die, block))
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
				start_think(table);
				get_forks(table);
				start_eat(table);
				start_sleep(table);
			}
		}
	}
	if (init_thread_monitoring(table->pids, table->starved_together,
			table->n_philosophers))
		return (1);
	wait_all_eat(table);
	return (0);
}
