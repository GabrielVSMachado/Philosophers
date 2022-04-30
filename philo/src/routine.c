/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:32:39 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/29 23:27:21 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "utils_actions.h"
#include "philo.h"

void	make_action(t_philo *philosopher, t_mls time_action)
{
	t_mls	future;

	future = get_current_time() + time_action;
	while (get_current_time() < future)
	{
		if (must_die(philosopher))
			die(philosopher);
		usleep(10);
	}
}

int	must_die(t_philo *philosopher)
{
	usleep(100);
	return (get_current_time() - philosopher->last_meal
		>= philosopher->table->die || philosopher->table->starved_together);
}

int	cant_eat_anymore(t_philo *philosophers)
{
	return (!philosophers->n_eat);
}

void	*dont_starve_together(void *block)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)block;
	philosophers->start_sim = get_current_time();
	philosophers->last_meal = philosophers->start_sim;
	while (1)
	{
		start_think(philosophers);
		wait_until_its_time(philosophers);
		get_forks(philosophers);
		start_eat(philosophers);
		start_sleep(philosophers);
	}
}
