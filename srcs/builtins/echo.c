/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sharsune <sharsune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:41:20 by Sharsune          #+#    #+#             */
/*   Updated: 2023/05/11 14:41:22 by Sharsune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	echo(char **args)
{
	int	i;
	int	newline;

	i = -1;
	newline = 1;
	while (args[++i])
	{
		if (ft_strcmp(args[i], "-n") == 0)
		{
			newline = 0;
			break ;
		}
	}
	i = -1;
	while (args[++i])
	{
		if (ft_strcmp(args[i], "echo") == 0 || \
		ft_strcmp(args[i], "-n") == 0)
			continue ;
		printf("%s", args[i]);
	}
	if (newline)
		printf("\n");
	return (0);
}
