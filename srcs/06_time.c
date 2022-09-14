/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_time.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 01:00:28 by efinicke          #+#    #+#             */
/*   Updated: 2022/03/24 19:38:22 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	waiting_act(int time_to_act)
{
	long	start;
	long	now;

	start = pinned_time();
	now = start;
	while (now < start + time_to_act)
	{
		usleep(100);
		now = pinned_time();
	}
}

long	pinned_time(void)
{
	struct timeval	st_time;

	if (gettimeofday(&st_time, NULL) == -1)
	{
		send_error(1, "pinned_time failure.");
		return (0);
	}
	return (st_time.tv_sec * 1000 + st_time.tv_usec / 1000);
}

long	get_time_since_pinned_time(long start)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		send_error(1, "get_time_since_pinned_time failure.");
		return (0);
	}
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000 - start);
}
