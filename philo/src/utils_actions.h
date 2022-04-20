/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_actions.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gvitor-s <gvitor-s>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 16:07:22 by gvitor-s          #+#    #+#             */
/*   Updated: 2022/04/20 16:32:07 by gvitor-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_ACTIONS_H
# define UTILS_ACTIONS_H

# include <pthread.h>

int		get_current_time(void);
void	get_fork_in_position(pthread_mutex_t *forks, int position, int seat);
#endif
