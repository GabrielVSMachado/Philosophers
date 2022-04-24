/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:32:39 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/23 21:43:15 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "utils_actions.h"
#include "philo.h"

void	*dont_starve_together(void *block)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)block;
	while (1)
	{
		start_think(&philosophers->thinking, philosophers->seat,
			philosophers->table);
		if (wait_until_its_time(philosophers)
			|| philosophers->table->starved_together)
			die(philosophers);
		if (get_forks(philosophers) || philosophers->table->starved_together)
			die(philosophers);
		start_eat(philosophers);
		start_sleep(philosophers);
	}
}
