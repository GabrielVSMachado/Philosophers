/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:32:39 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/21 18:41:29 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "utils_actions.h"
#include "philo.h"

void	*start_dinner(void *block)
{
	t_philo	*philosophers;

	philosophers = (t_philo *)block;
	while (1)
	{
		start_think(&philosophers->thinking, philosophers->seat);
		if (philosophers->table->n_philophers > 1)
		{
			if (philosophers->seat % 2)
			{
				if (wait_until_even_end(philosophers))
					return (die(philosophers->seat, philosophers->thinking));
			}
			else
			{
				if (wait_until_odd_end(philosophers))
					return (die(philosophers->seat, philosophers->thinking));
			}
		}
		if (get_forks(philosophers))
			return (die(philosophers->seat, philosophers->thinking));
		start_eat(philosophers);
		start_sleep(philosophers);
	}
}
