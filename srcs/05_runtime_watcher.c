/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_runtime_watcher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:20:36 by efinicke          #+#    #+#             */
/*   Updated: 2022/03/24 19:47:24 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	fatal_issue(t_env *env)
{
	pthread_mutex_lock(env->death_census);
	if (env->death == 1)
	{
		pthread_mutex_unlock(env->death_census);
		return (1);
	}
	pthread_mutex_unlock(env->death_census);
	return (0);
}

int	ate(t_philo *philo, t_env *env)
{
	pthread_mutex_lock(&env->check_ate[philo->id]);
	if (!philo->meals_nb)
	{
		pthread_mutex_unlock(&env->check_ate[philo->id]);
		return (1);
	}
	pthread_mutex_unlock(&env->check_ate[philo->id]);
	return (0);
}

int	empty_meals_stock(t_env *env)
{
	pthread_mutex_lock(env->ate_census);
	if (env->ate == env->philo_nb)
	{
		pthread_mutex_unlock(env->ate_census);
		return (1);
	}
	pthread_mutex_unlock(env->ate_census);
	return (0);
}

void	runtime_watcher(t_env *env)
{
	int		i;
	int		time;

	i = -1;
	time = 0;
	while (++i < env->philo_nb)
	{
		pthread_mutex_lock(&env->check_ate[i]);
		time = get_time_since_pinned_time(env->philo[i].last_meal_start);
		pthread_mutex_unlock(&env->check_ate[i]);
		if (ate(&env->philo[i], env))
			break ;
		if (time > env->ttdie)
		{
			print_die(env, i);
			break ;
		}
	}
}

void	*mainthrd(void *philo_env)
{
	t_env	*env;

	env = (t_env *)philo_env;
	while (!fatal_issue(env) && !empty_meals_stock(env))
	{
		usleep(1000);
		runtime_watcher(env);
	}
	return (NULL);
}
