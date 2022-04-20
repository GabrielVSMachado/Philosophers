/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 19:32:39 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/20 20:00:00 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "utils_actions.h"
#include "philo.h"

void	*start_dinner(void *block)
{
	struct s_table	*table;

	table = (struct s_table *)block;
	while (1)
	{
		start_think(&table->philosophers->thinking, table->philosophers->seat);
		if (table->philosophers->seat % 2)
		{
			if (wait_until_even_end(table))
				return (die(table->philosophers->seat));
		}
		else
		{
			if (wait_until_odd_end(table))
				return (die(table->philosophers->seat));
		}
		if (get_forks(table))
			return (die(table->philosophers->seat));
		start_eat(table);
		start_sleep(table);
	}
}
