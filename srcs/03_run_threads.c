/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_run_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:28:31 by efinicke          #+#    #+#             */
/*   Updated: 2022/03/04 22:22:15 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	run_threads(t_env *env)
{
	pthread_t	thrd;
	int			nb;
	int			time;
	int			i;

	nb = env->philo_nb;
	time = env->ttsleep * 500;
	pthread_create(&thrd, NULL, mainthrd, env);
	i = -1;
	while (++i <= nb / 2 && 2 * i < nb)
		pthread_create(&env->thrds[i * 2], NULL, routine, &env->philo[i * 2]);
	usleep(time);
	i = -1;
	while (++i < nb / 2)
		pthread_create(&env->thrds[i * 2 + 1], \
		NULL, routine, &env->philo[i * 2 + 1]);
	threads_end(env);
	pthread_join(thrd, NULL);
	return (1);
}
