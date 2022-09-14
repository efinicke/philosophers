/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_fill_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 14:28:35 by efinicke          #+#    #+#             */
/*   Updated: 2022/03/24 21:07:45 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	alloc_env(t_env *env)
{
	env->philo = malloc(sizeof(t_philo) * env->philo_nb);
	env->thrds = malloc(sizeof(pthread_t) * (env->philo_nb + 1));
	env->fork = malloc(sizeof(pthread_mutex_t) * (env->philo_nb + 4));
	env->check_ate = malloc(sizeof(pthread_mutex_t) * (env->philo_nb));
	if (!env->fork || !env->philo || !env->thrds || !env->check_ate)
		return (0);
	mem_set (env->fork, 0, sizeof(pthread_mutex_t) * (env->philo_nb + 4));
	mem_set (env->check_ate, 0, sizeof(pthread_mutex_t) * (env->philo_nb));
	mem_set (env->thrds, 0, sizeof(pthread_t) * (env->philo_nb + 1));
	return (1);
}

int	init_mutex(t_env *env, int i, int ret)
{
	i = -1;
	while (++i < (env->philo_nb + 4))
	{
		ret = pthread_mutex_init(&env->fork[i], NULL);
		if (ret != 0)
		{
			send_error(1, "mutex_init failure.");
			printf("ret code [%d] : %d\n", ret, i);
			return (0);
		}
	}
	i = -1;
	while (++i < (env->philo_nb))
	{
		ret = pthread_mutex_init(&env->check_ate[i], NULL);
		if (ret != 0)
		{
			send_error(1, "mutex_init failure.");
			printf("ret code [%d] : %d\n", ret, i);
			return (0);
		}
	}
	return (1);
}

void	fill_argv(t_env *env, int argc, char **argv)
{
	env->philo_nb = atoi_parser(argv[1]);
	env->ttdie = atoi_parser(argv[2]);
	env->tteat = atoi_parser(argv[3]);
	env->ttsleep = atoi_parser(argv[4]);
	if (argc == 6)
		env->must_eat = atoi_parser(argv[5]);
	else
	{
		env->must_eat = -1;
		env->ate = -1;
	}
}

void	fill_philos(t_env *env)
{
	int	i;

	i = -1;
	while (++i < env->philo_nb)
	{
		env->philo[i].id = i;
		env->philo[i].meals_nb = env->must_eat;
		env->philo[i].right = &env->fork[i + 4];
		if (i == 0)
			env->philo[i].left = &env->fork[i + 4];
		env->philo[0].right = &env->fork[env->philo_nb + 4 - 1];
		if (i > 0)
			env->philo[i].left = &env->fork[i + 4 - 1];
		env->philo[i].env = env;
	}
	if (env->philo_nb == 1)
		env->philo[0].right = NULL;
	env->init_time = pinned_time();
	i = -1;
	while (++i < env->philo_nb)
		env->philo[i].last_meal_start = env->init_time;
}

int	fill_env(t_env *env, int argc, char **argv)
{
	fill_argv(env, argc, argv);
	env->death = 0;
	env->ate = 0;
	if (!alloc_env(env) || !init_mutex(env, -1, 0))
	{
		free_env(env);
		return (0);
	}
	env->death_census = &env->fork[0];
	env->ate_census = &env->fork[1];
	env->print = &env->fork[3];
	fill_philos(env);
	return (1);
}
