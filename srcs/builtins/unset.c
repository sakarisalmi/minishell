/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sharsune <sharsune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:43:03 by Sharsune          #+#    #+#             */
/*   Updated: 2023/05/11 14:43:05 by Sharsune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset(char **args)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (args[i++])
	{
		while (*envs++)
		{
			if (ft_strncmp(*envs, args[i], ft_strlen(args[i])) == 0)
			{
				while (envs[j])
				{
					envs[j] = envs[j +1];
					j++;
				}
				break ;
			}
		}
	}
	return (0);
}
