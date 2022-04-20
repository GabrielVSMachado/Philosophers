/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:25:24 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/06 19:44:04 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "philo.h"
#include <unistd.h>

int	main(int argc, char **argv)
{
	if (argc < 4)
	{
		write(STDERR_FILENO, "Too few arguments!\n", 20);
		return (1);
	}
	if (check_inputs(argv))
	{
		write(STDERR_FILENO, "Invalid argument passed!\n", 20);
		return (1);
	}
	return (0);
}
