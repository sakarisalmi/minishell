/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 13:46:06 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/27 14:12:29 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

/*----------------------------------------------------------------------------*/

char	**export_add_new_var(char *new_str, char **envs, t_data *data)
{
	char	*str_plus;
	int		i;

	printf("in export_add_new_var\n");
	i = 0;
	while (new_str[i] && new_str[i] != '+')
		i++;
	printf("stage 1\n");
	if (new_str[i] == '+')
	{
		printf("stage 2\n");
		str_plus = ms_calloc(ft_strlen(new_str), sizeof(char), data);
		printf("stage 3\n");
		ft_strncat(str_plus, new_str, i);
		printf("stage 4\n");
		printf("new_str: %s\n", str_plus);
		ft_strncat(str_plus, &new_str[i + 1], ft_strlen(&new_str[i + 1]));
		printf("new_str: %s\n", str_plus);
		envs = str_array_add_str(envs, str_plus);
	}
	else
		envs = str_array_add_str(envs, new_str);
	return (envs);
}
