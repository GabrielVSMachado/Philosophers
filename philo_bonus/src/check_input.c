/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:04:28 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/26 15:31:15 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	isdigit(int c)
{
	return (c <= '9' && c >= '0');
}

static int	is_valid_arg(char *arg)
{
	if (*arg == '\0')
		return (0);
	arg += (*arg == '+');
	while (arg && *arg && isdigit(*arg))
		arg++;
	return (*arg == '\0');
}

int	check_inputs(char *const *argv)
{
	int	counter;

	counter = 0;
	while (argv[++counter] && is_valid_arg(argv[counter]))
		;
	return (argv[counter] != NULL);
}
