/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:34:55 by Sharsune          #+#    #+#             */
/*   Updated: 2023/05/18 14:40:15 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*----------------------------------------------------------------------------*/

int	export(char **args, t_data *data)
{
	if (!args[1])
	{
		export_print(data);
		return (0);
	}
	

}

static void	export_print(t_data *data)
{
	int	i;

	i = -1;
	while (data->envs[++i])
	{
		printf("declare -x ");
		printf("%s\n", data->envs[i]);
	}
}

static int	export_find_match(char str, t_data *data)
{
	char	*var_name;



	return (0);
}
