/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 02:14:13 by efinicke          #+#    #+#             */
/*   Updated: 2022/03/24 21:07:23 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	threads_end(t_env *env)
{
	int	i;
	int	ret;

	ret = 0;
	i = -1;
	while (++i < env->philo_nb)
	{
		ret = pthread_join(env->thrds[i], NULL);
		if (ret != 0)
		{
			send_error(1, "threads_end failure.");
			printf("ret code [%d] : %d\n", i, ret);
			return (0);
		}
	}
	return (1);
}

int	mutex_end(t_env *env, int i, int ret)
{
	while (++i < (env->philo_nb + 4))
	{
		ret = pthread_mutex_destroy(&(env->fork[i]));
		if (ret != 0)
		{
			send_error(1, "mutex_end failure.");
			printf("ret code [%d] : %d\n", ret, i);
			return (0);
		}
	}
	while (++i < (env->philo_nb))
	{
		ret = pthread_mutex_destroy(&(env->check_ate[i]));
		if (ret != 0)
		{
			send_error(1, "mutex_end failure.");
			printf("ret code [%d] : %d\n", ret, i);
			return (0);
		}
	}
	return (1);
}

void	free_env(t_env *env)
{
	if (env->thrds)
		free(env->thrds);
	if (env->fork)
		free(env->fork);
	if (env->check_ate)
		free(env->check_ate);
	if (env->philo)
		free(env->philo);
}
