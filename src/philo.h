/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 16:01:14 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/06 19:54:09 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

struct s_table
{
	pthread_t		*philo;
	pthread_mutex_t	*mtx;
	int				*fork;
};

int	check_inputs(char **argv);
#endif
