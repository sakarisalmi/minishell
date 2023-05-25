/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:52:34 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/25 12:37:54 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(char **args, t_data *data)
{
	int	i;

	i = 0;
	if (args[1])
	{
		ft_putendl_fd("MINISHELL: env: give no arguments or options", 2);
		return (127);
	}
	else
	{
		while (data->envs[i])
		{
			if (ft_strchr(data->envs[i], '='))
				printf("%s\n", data->envs[i]);
			i++;
		}
		return (0);
	}
}
