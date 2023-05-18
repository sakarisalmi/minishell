/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:43:03 by Sharsune          #+#    #+#             */
/*   Updated: 2023/05/18 16:04:03 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset(char **args, t_data *data)
{
	int	i;
	int	j;

	i = 1;
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
