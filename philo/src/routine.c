/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:32:39 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/24 17:58:26 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "utils_actions.h"
#include "philo.h"

int	must_die(t_mls last_meal, t_mls die)
{
	return (get_current_time() - last_meal >= die);
}

int	cant_eat_anymore(t_philo *philosophers)
{
	int	finished;

	pthread_mutex_lock(&philosophers->table->printlock);
	finished = !philosophers->n_eat;
	pthread_mutex_unlock(&philosophers->table->printlock);
	return (finished);
}

int	someone_is_starved(t_philo *philosophers)
{
	int	starved;

	pthread_mutex_lock(&philosophers->table->printlock);
	starved = philosophers->table->starved_together;
	pthread_mutex_unlock(&philosophers->table->printlock);
	return (starved);
}

void	*dont_starve_together(void *block)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)block;
	philosophers->start_sim = get_current_time();
	while (1)
	{
		start_think(philosophers);
		wait_until_its_time(philosophers);
		get_forks(philosophers);
		start_eat(philosophers);
		start_sleep(philosophers);
	}
}
