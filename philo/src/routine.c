/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:32:39 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/30 19:30:32 by gvitor-s         ###   ########.fr       */
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
	int	someone_die;

	usleep(40);
	pthread_mutex_lock(&philosopher->table->check_is_dead);
	someone_die = philosopher->table->starved_together;
	pthread_mutex_unlock(&philosopher->table->check_is_dead);
	return (get_current_time() - philosopher->last_meal
		>= philosopher->table->die || someone_die);
}

int	cant_eat_anymore(t_philo *philosophers)
{
	return (!philosophers->n_eat);
}

void	*dont_starve_together(void *block)
{
	t_philo		*philosophers;
	int			its_your_time;
	t_waiter	*waiter;

	philosophers = (t_philo *)block;
	philosophers->start_sim = get_current_time();
	philosophers->last_meal = philosophers->start_sim;
	waiter = philosophers->table->semaphoro;
	while (1)
	{
		if (!philosophers->thinking)
			start_think(philosophers);
		pthread_mutex_lock(&philosophers->table->check_your_time);
		its_your_time = waiter[philosophers->seat - 1].smp;
		pthread_mutex_unlock(&philosophers->table->check_your_time);
		if (its_your_time)
		{
			get_forks(philosophers);
			start_eat(philosophers);
			start_sleep(philosophers);
		}
		if (must_die(philosophers))
			die(philosophers);
	}
}
