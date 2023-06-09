/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_unpacker_get_var.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:04:44 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/07 15:14:35 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

char		*token_unpacker_hit_var(char *rl_part, char *token,
				t_token_unpacker *tunp, t_data *data);
static char	*token_unpacker_get_var(char *rl_part, char *token,
				t_token_unpacker *tunp, t_data *data);
char		*token_unpacker_get_var_from_env(char *var_name, t_data *data);
static char	*token_unpacker_get_last_exit(char *rl_part, char *token,
				t_token_unpacker *tunp, t_data *data);
static void	set_token_unpacker_var_struct_vals(t_token_unpacker_var *f);

/*----------------------------------------------------------------------------*/

/*	This function is called if during the token_unpacker functions the
	dollar-sign is found. This function was made to save space in
	tunp_outside_quotes and tunp_in_quotes. */
char	*token_unpacker_hit_var(char *rl_part, char *token,
	t_token_unpacker *f, t_data *data)
{
	if (ft_isspace(rl_part[f->i + 1]) || rl_part[f->i + 1] == '\0'
		|| (f->in_quotes && (rl_part[f->i + 1] == '"'
				|| rl_part[f->i + 1] == '\'')))
	{
		f->token_length++;
		token = ms_realloc(token, f->token_length, data);
		ft_strncat(token, "$", 1);
		f->i++;
		return (token);
	}
	else if (rl_part[f->i + 1] == '?')
		return (token_unpacker_get_last_exit(rl_part, token, f, data));
	else
		return (token_unpacker_get_var(rl_part, token, f, data));
	return (NULL);
}

/*	This function handles the retrieving of environmental variables
	that are preceded by a $-sign. We check for the variable
	in the environment and if there is no match, we return NULL.*/
static char	*token_unpacker_get_var(char *rl_part, char *token,
	t_token_unpacker *tunp, t_data *data)
{
	t_token_unpacker_var	f;

	set_token_unpacker_var_struct_vals(&f);
	tunp->i++;
	f.j = tunp->i;
	while (ft_isalnum(rl_part[f.j]) || rl_part[f.j] == '_')
		f.j++;
	f.var_name = ms_calloc(f.j - tunp->i + 1, sizeof(char), data);
	ft_strncpy(f.var_name, rl_part + tunp->i, f.j - tunp->i);
	tunp->i = f.j;
	f.result = token_unpacker_get_var_from_env(f.var_name, data);
	if (!f.result)
		return (token);
	tunp->token_length += ft_strlen(f.result);
	token = (char *)ms_realloc(token, tunp->token_length, data);
	ft_strncat(token, f.result, ft_strlen(f.result));
	free (f.result);
	return (token);
}

char	*token_unpacker_get_var_from_env(char *var_name, t_data *data)
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
			ft_bzero(var_name, ft_strlen(var_name));
			free(var_name);
			return (ft_strdup(data->envs[i] + var_name_len + 1));
		}
		i++;
	}
	ft_bzero(var_name, ft_strlen(var_name));
	free(var_name);
	return (NULL);
}

/*	This function is called if the next char after the dollar-sign
	is the question-mark. Will get the latest exit_status from data.*/
static char	*token_unpacker_get_last_exit(char *rl_part, char *token,
	t_token_unpacker *tunp, t_data *data)
{
	char	*result;

	(void)rl_part;
	tunp->i += 2;
	result = ft_itoa(data->latest_exit_status);
	if (!result)
		minishell_fatal_error_exit(data);
	tunp->token_length += ft_strlen(result);
	token = (char *)ms_realloc(token, tunp->token_length, data);
	ft_strncat(token, result, ft_strlen(result));
	free(result);
	return (token);
}

static void	set_token_unpacker_var_struct_vals(t_token_unpacker_var *f)
{
	f->j = 0;
	f->result = NULL;
	f->var_name = NULL;
}
