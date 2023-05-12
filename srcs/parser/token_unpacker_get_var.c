/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_unpacker_get_var.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:04:44 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/11 14:58:38 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

char		*token_unpacker_hit_var(char *rl_part, char *token,
				t_token_unpacker *tunp, t_data *data);
static char	*token_unpacker_get_var(char *rl_part, char *token,
				t_token_unpacker *tunp, t_data *data);
static char	*token_unpacker_get_var_from_env(char *var_name, t_data *data);
static char	*token_unpacker_get_last_exit(char *rl_part, char *token,
				t_token_unpacker *tunp, t_data *data);

/*----------------------------------------------------------------------------*/

/*	This function is called if during the token_unpacker functions the
	dollar-sign is found. This function was made to save space in
	tunp_outside_quotes and tunp_in_quotes. */
char	*token_unpacker_hit_var(char *rl_part, char *token,
	t_token_unpacker *tunp, t_data *data)
{
	if (rl_part[tunp->i + 1] == '?')
		return (token_unpacker_get_last_exit(rl_part, token, tunp, data));
	else
		return (token_unpacker_get_var(rl_part, token, tunp, data));
	return (NULL);
}

/*	This function handles the retrieving of environmental variables
	that are preceded by a $-sign. We check for the variable
	in the environment and if there is no match, we return NULL.*/
static char	*token_unpacker_get_var(char *rl_part, char *token,
	t_token_unpacker *tunp, t_data *data)
{
	t_token_unpacker_var	f;

	tunp->i++;
	f.j = tunp->i;
	while (ft_isalnum(rl_part[f.j]) || rl_part[f.j] == '_')
		f.j++;
	f.var_name = ft_calloc(f.j - tunp->i, sizeof(char));
	if (!f.var_name)
	{
		tunp->i = f.j;
		ft_putendl_fd("tunp_get_var malloc failure", 2);
		return (token);
	}
	ft_strncpy(f.var_name, rl_part + tunp->i, f.j - tunp->i);
	tunp->i = f.j;
	f.result = token_unpacker_get_var_from_env(f.var_name, data);
	if (!f.result)
		return (token);
	token = (char *)ft_realloc(token, ft_strlen(rl_part) + ft_strlen(f.result));
	ft_strncat(token, f.result, ft_strlen(f.result));
	free (f.result);
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
		if (ft_strnstr(data->envs[i], var_name, var_name_len)
			&& data->envs[i][var_name_len] == '=')
		{
			free(var_name);
			return (ft_strdup(data->envs[i] + var_name_len + 1));
		}
		i++;
	}
	free(var_name);
	return (NULL);
}

/*	This function is called if the next char after the dollar-sign
	is the question-mark. Will get the latest exit_status from data.*/
static char	*token_unpacker_get_last_exit(char *rl_part, char *token,
	t_token_unpacker *tunp, t_data *data)
{
	char	*result;

	tunp->i += 2;
	result = ft_itoa(data->latest_exit_status);
	token = (char *)ft_realloc(token, ft_strlen(rl_part) + ft_strlen(result));
	ft_strncat(token, result, ft_strlen(result));
	free(result);
	return (token);
}
