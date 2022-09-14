/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_philo_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 00:05:04 by efinicke          #+#    #+#             */
/*   Updated: 2022/03/24 20:07:26 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	take_forks(t_philo *philo, t_env *env)
{
	pthread_mutex_lock(philo->right);
	print_state(philo, env, R_FORK);
	pthread_mutex_lock(philo->left);
	print_state(philo, env, L_FORK);
}

void	dining_moment(t_philo *philo, t_env *env)
{
	pthread_mutex_lock(&env->check_ate[philo->id]);
	philo->last_meal_start = pinned_time();
	philo->meals_nb--;
	pthread_mutex_unlock(&env->check_ate[philo->id]);
	print_state(philo, env, EAT);
	waiting_act(env->tteat);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
}

void	philo_routine(t_philo *philo, t_env *env)
{
	int	i;

	i = 0;
	while (++i != 0)
	{
		take_forks(philo, env);
		dining_moment(philo, env);
		print_state(philo, env, SLEEP);
		waiting_act(env->ttsleep);
		print_state(philo, env, THINK);
		if (fatal_issue(env))
			break ;
		if (philo->meals_nb == 0)
			break ;
	}
}

void	*routine(void *philo_env)
{
	t_philo	*philo;
	t_env	*env;

	philo = (t_philo *)philo_env;
	env = (t_env *)philo->env;
	if (philo->id == 0 && philo->right == NULL)
	{
		print_state(philo, env, R_FORK);
		waiting_act(env->ttdie + 42);
		return (0);
	}
	else
		philo_routine(philo, env);
	pthread_mutex_lock(env->ate_census);
	env->ate += 1;
	pthread_mutex_unlock(env->ate_census);
	return (NULL);
}
