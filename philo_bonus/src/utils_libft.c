/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 21:05:41 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/07 22:14:58 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	is_space(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	return (0);
}

static int	isdigit(int c)
{
	return (c <= '9' && c >= '0');
}

int	ft_atoi(const char *str)
{
	int	minus_signal;
	int	result;

	minus_signal = 0;
	while (is_space(*str))
		str++;
	minus_signal = (*str == '-');
	str += ((*str == '+') || (minus_signal));
	result = 0;
	while (*str && isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * (!minus_signal) - result * minus_signal);
}
