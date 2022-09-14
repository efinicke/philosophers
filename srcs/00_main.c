/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 18:39:07 by efinicke          #+#    #+#             */
/*   Updated: 2022/03/24 19:23:45 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

int	main(int argc, char **argv)
{
	t_env	env;

	if (!parse_argv(argc, argv))
		return (0);
	if (!fill_env(&env, argc, argv))
		return (0);
	if (!run_threads(&env))
		return (0);
	if (!mutex_end(&env, -1, 0))
		return (0);
	free_env(&env);
	return (1);
}
