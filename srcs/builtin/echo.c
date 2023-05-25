/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:41:20 by Sharsune          #+#    #+#             */
/*   Updated: 2023/05/25 16:22:50 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			echo(char **args);
static int	echo_check_for_options(char **args, int *idx);
static int	echo_check_if_arg_is_option(char *arg);

/*----------------------------------------------------------------------------*/

int	echo(char **args)
{
	int	i;
	int	no_newline;

	i = -1;
	no_newline = echo_check_for_options(args, &i);
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (!no_newline)
		printf("\n");
	return (0);
}

/*	This function checks if there are any options for echo;
	it sets the int pointer to the argument where the possible
	options end. The function returns 0 if there is no options. */
static int	echo_check_for_options(char **args, int *idx)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (args[++i])
	{
		if (!echo_check_if_arg_is_option(args[i]))
		{
			*idx = i;
			return (result);
		}
		result = 1;
	}
	*idx = i;
	return (result);
}

/*	This function checks if the given argument is an option. */
static int	echo_check_if_arg_is_option(char *arg)
{
	int	i;

	i = -1;
	if (arg[0] == '\0')
		return (0);
	while (arg[++i])
	{
		if (i == 0)
		{
			if (arg[i] != '-')
				return (0);
		}
		else
		{
			if (arg[i] != 'n')
				return (0);
		}
	}
	return (1);
}
