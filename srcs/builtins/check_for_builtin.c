/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 17:29:37 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/05 16:06:56 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"

/*	This function checks if there is a command in the tokens array and if that
	command is a built-in.	Returns 1 if there is an built-in, otherwise
	returns 0.	*/
int	check_for_builtin(t_token **tokens_array)
{
	int		i;

	i = 0;
	while (tokens_array[i])
	{
		if (tokens_array[i]->type == T_COMMAND)
		{
			if (ft_strncmp_casein(tokens_array[i]->string, "cd", 2) == 0)
				return (1);
			if (ft_strncmp_casein(tokens_array[i]->string, "echo", 4) == 0)
				return (1);
			if (ft_strncmp_casein(tokens_array[i]->string, "pwd", 3) == 0)
				return (1);
			if (ft_strncmp_casein(tokens_array[i]->string, "export", 6) == 0)
				return (1);
			if (ft_strncmp_casein(tokens_array[i]->string, "unset", 5) == 0)
				return (1);
			if (ft_strncmp_casein(tokens_array[i]->string, "env", 3) == 0)
				return (1);
			if (ft_strncmp_casein(tokens_array[i]->string, "exit", 4) == 0)
				return (1);
		}
		i++;
	}
	return (0);
}