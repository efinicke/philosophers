/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 19:47:11 by efinicke          #+#    #+#             */
/*   Updated: 2022/03/24 19:54:10 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

void	print_state(t_philo *philo, t_env *env, char *print)
{
	if (!fatal_issue(env))
	{
		pthread_mutex_lock(env->print);
		printf("%ld %d %s\n", \
		get_time_since_pinned_time(env->init_time), \
			philo->id + 1, \
			print);
		pthread_mutex_unlock(env->print);
	}	
}

void	print_die(t_env *env, int i)
{
	if (!fatal_issue(env))
	{
		pthread_mutex_lock(env->death_census);
		env->death = 1;
		pthread_mutex_unlock(env->death_census);
		usleep(1000);
		pthread_mutex_lock(env->print);
		printf("%ld %d %s\n", \
			get_time_since_pinned_time(env->init_time), \
			i + 1, \
			DIE);
		pthread_mutex_unlock(env->print);
	}
}

static void	red(void)
{
	printf("\033[0;31m");
}

static void	reset(void)
{
	printf("\033[0m");
}

void	send_error(int error, char *error_message)
{
	char	*error_form;

	error_form = "Error";
	red();
	if (error == 1)
		printf("%s\n", error_form);
	printf("%s\n", error_message);
	reset();
}
