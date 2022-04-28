/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:32:39 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/28 23:16:40 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "utils_actions.h"
#include "philo.h"

int	must_die(t_philo *philosopher)
{
	return (get_current_time() - philosopher->last_meal
		>= philosopher->table->die);
}

int	cant_eat_anymore(t_philo *philosophers)
{
	return (!philosophers->n_eat);
}

int	someone_is_starved(t_philo *philosophers)
{
	return (philosophers->table->starved_together);
}

void	*dont_starve_together(void *block)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)block;
	philosophers->start_sim = get_current_time();
	philosophers->last_meal = philosophers->start_sim;
	while (1)
	{
		if (someone_is_starved(philosophers))
			pthread_exit(NULL);
		start_think(philosophers);
		wait_until_its_time(philosophers);
		get_forks(philosophers);
		start_eat(philosophers);
		start_sleep(philosophers);
	}
}
