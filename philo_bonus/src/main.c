/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:21:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/27 19:08:37 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_bonus.h"
#include "utils_actions.h"

int	main(int argc, char *const *argv)
{
	struct s_table	*table;

	if (argc < 4 || argc > 6)
	{
		if (argc < 4)
			write(STDERR_FILENO, "Too few arguments!\n", 19);
		else
			write(STDERR_FILENO, "Too many arguments!\n", 20);
		return (1);
	}
	if (check_inputs(argv))
	{
		write(STDERR_FILENO, "Wrong argument passed!\n", 24);
		return (1);
	}
	table = init_table(ft_atoi(argv[1]), argv);
	if (!table)
	{
		write(STDERR_FILENO, "Error on malloc struct table!\n", 31);
		return (1);
	}
	if (dont_starved_together(table, argv[5]))
	{
		write(STDERR_FILENO, "Error on create thread!\n", 25);
		return (1);
	}
	destroy_table(&table);
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/starved_together");
	sem_unlink("/your_time");
	return (0);
}
