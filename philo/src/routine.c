/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:32:39 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/22 17:56:36 by gvitor-s         ###   ########.fr       */
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
		start_think(&philosophers->thinking, philosophers->seat);
		if (wait_until_its_time(philosophers)
			|| philosophers->table->starved_together)
			return (die(philosophers->seat, philosophers->thinking,
					&philosophers->table->starved_together));
		if (get_forks(philosophers) || philosophers->table->starved_together)
			return (die(philosophers->seat, philosophers->thinking,
					&philosophers->table->starved_together));
		start_eat(philosophers);
		if (philosophers->table->starved_together)
			return (NULL);
		start_sleep(philosophers);
		if (philosophers->table->starved_together)
			return (NULL);
	}
}
