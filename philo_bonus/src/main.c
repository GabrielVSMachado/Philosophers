/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 21:21:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/26 15:30:48 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "philo_bonus.h"

int	main(int argc, char *const *argv)
{
	if (argc < 4 || argc > 6)
	{
		if (argc < 4)
			write(STDERR_FILENO, "Too few arguments\n", 19);
		else
			write(STDERR_FILENO, "Too many arguments\n", 20);
		return (1);
	}
	if (check_inputs(argv))
	{
		write(STDERR_FILENO, "Wrong argument passed!\n", 24);
		return (1);
	}
	return (0);
}
