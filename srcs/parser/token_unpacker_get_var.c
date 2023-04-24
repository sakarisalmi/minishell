/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_unpacker_get_var.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:04:44 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/24 15:09:04 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenize.h"

char		*token_unpacker_get_var(char *rl_part, char *token,
				t_token_unpacker *tunp, t_data *data);
static char	*token_unpacker_get_var_from_env(char *var_name, t_data *data);
char		*token_unpacker_skip_var(char *rl_part, t_token_unpacker *tunp);

/*----------------------------------------------------------------------------*/

/*	This function handles the retrieving of shell or environmental variables
	that are preceded by a $-sign. We check for the variable
	in the environment and if there is no match, we return NULL.*/
char	*token_unpacker_get_var(char *rl_part, char *token,
	t_token_unpacker *tunp, t_data *data)
{
	char	*var_name;
	char	*var_result;
	int		j;

	tunp->i++;
	j = tunp->i;
	while (ft_isalnum(rl_part[j]))
		j++;
	var_name = malloc((j - tunp->i) * sizeof(char));
	if (!var_name)
	{
		tunp->i = j;
		// remove later?
		printf("tunp_get_var malloc failure\n");
		return (token);
	}
	ft_strncpy(var_name, rl_part + tunp->i, j - tunp->i);
	tunp->i = j;
	if (!var_name || ft_strlen(var_name) == 0)
		return (token);
	var_result = token_unpacker_get_var_from_env(var_name, data);
	free (var_name);
	token = (char *)ft_realloc(token, ft_strlen(rl_part) + ft_strlen(var_result));
	ft_strncat(token, var_result, ft_strlen(var_result));
	free (var_result);
	return (token);
}

static char	*token_unpacker_get_var_from_env(char *var_name, t_data *data)
{
	int		var_name_len;
	int		i;

	var_name_len = ft_strlen(var_name);
	i = 0;
	while (data->envs[i] != NULL)
	{
		if (ft_strnstr(data->envs[i], var_name, var_name_len))
			return (ft_strdup(data->envs[i] + var_name_len + 1));
		i++;
	}
	return (NULL);
}

/*	This function simply skips the variable name, because if the $-sign
	is preceded by any non whitespace character the variable will be NULL. */
char	*token_unpacker_skip_var(char *rl_part, t_token_unpacker *tunp)
{
	tunp->i++;
	while (ft_isalnum(rl_part[tunp->i]))
		tunp->i++;
	return (NULL);
}
