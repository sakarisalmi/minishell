/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 14:52:34 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/18 14:30:27 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	env(t_data *data)
{
	int	i;

	i = 0;
	while (data->envs[i])
	{
		if (ft_strchr(data->envs[i], '='))
			printf("%s\n", data->envs[i]);
		i++;
	}
	return (0);
}
