/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:58:10 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/19 15:12:50 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

char	*export_create_new_var(char *str)
{
	char	*new_var;
	int		i;

	printf("in export create new var\n");
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
	{
		new_var = ft_calloc(ft_strlen(str) + 3, sizeof(char));
		ft_strncat(new_var, str, ++i);
		ft_strncat(new_var, "\"", 1);
		ft_strncat(new_var, str + i, ft_strlen(str + i));
		ft_strncat(new_var, "\"", 1);
	}
	else
		new_var = ft_strdup(str);
	return (new_var);
}
