/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_unpacker_get_var.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:04:44 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/11 14:35:04 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

char		*token_unpacker_hit_var(char *rl_part, char *token,
				t_token_unpacker *tunp, t_data *data);
char		*token_unpacker_get_var(char *rl_part, char *token,
				t_token_unpacker *tunp, t_data *data);
static char	*token_unpacker_get_var_from_env(char *var_name, t_data *data);
char		*token_unpacker_skip_var(char *rl_part, t_token_unpacker *tunp);
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

/*	This function handles the retrieving of shell or environmental variables
	that are preceded by a $-sign. We check for the variable
	in the environment and if there is no match, we return NULL.*/
char	*token_unpacker_get_var(char *rl_part, char *token,
	t_token_unpacker *tunp, t_data *data)
{
	char	*var_name;
	char	*result;
	int		j;

	tunp->i++;
	j = tunp->i;
	while (ft_isalnum(rl_part[j]) || rl_part[j] == '_')
		j++;
	var_name = ft_calloc(j - tunp->i, sizeof(char));
	if (!var_name)
	{
		tunp->i = j;
		ft_putstr_fd("tunp_get_var malloc failure\n", 2);
		return (token);
	}
	ft_strncpy(var_name, rl_part + tunp->i, j - tunp->i);
	tunp->i = j;
	if (!var_name || ft_strlen(var_name) == 0)
		return (token);
	result = token_unpacker_get_var_from_env(var_name, data);
	if (!result)
		return (token);
	free (var_name);
	token = (char *)ft_realloc(token, ft_strlen(rl_part) + ft_strlen(result));
	ft_strncat(token, result, ft_strlen(result));
	free (result);
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
	while (ft_isalnum(rl_part[tunp->i]) || rl_part[tunp->i] == '_')
		tunp->i++;
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
