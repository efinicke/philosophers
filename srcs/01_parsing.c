/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: efinicke <efinicke@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/30 22:29:00 by efinicke          #+#    #+#             */
/*   Updated: 2022/03/24 19:24:15 by efinicke         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philosophers.h"

static int	err_negative_val(char c)
{
	if (c == '-')
	{
		send_error(1, "All arguments must contain positive values.");
		return (1);
	}
	return (0);
}

static int	err_isnt_digit(char c)
{
	if (!is_digit(c) && c != '\0')
	{
		send_error(1, "Only numbers are required as arguments.");
		return (1);
	}
	return (0);
}

static int	err_int_max(long int nbr)
{
	if (nbr > INT_MAX)
	{
		send_error(1, "The values doesn't exceeds the INT_MAX size.");
		return (1);
	}
	return (0);
}

int	atoi_parser(char *arg)
{
	int			i;
	long int	nbr;

	i = 0;
	nbr = 0;
	while ((arg[i] == ' ') || (arg[i] >= '\t' && arg[i] <= '\r'))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (err_negative_val(arg[i]))
			return (-1);
		i++;
	}
	if (err_isnt_digit(arg[i]))
		return (-1);
	while (is_digit(arg[i]))
	{
		nbr = nbr * 10 + arg[i] - 48;
		i++;
	}
	if (err_int_max(nbr))
		return (-1);
	if (err_isnt_digit(arg[i]))
		return (-1);
	return (nbr);
}

int	parse_argv(int argc, char **argv)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	if (argc < 5 || argc > 6)
	{
		send_error(1, USAGE);
		return (0);
	}
	while (argv[++i] && (i < argc))
	{
		nb = atoi_parser(argv[i]);
		if (nb == -1 || nb == 0)
		{
			if (nb == 0)
				send_error(1, "Null can not be a valid value.");
			if (nb == -1 || nb == 0)
				send_error(0, "Env is not correctly initialized.");
			return (0);
		}
	}
	return (1);
}
