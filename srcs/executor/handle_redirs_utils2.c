/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:06:06 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/17 14:49:37 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/tokenizer.h"
#include "../../include/executor.h"

int			get_process_idx(t_process *proc, t_data *data);
int			handle_redir_lesser_lesser_here_doc(t_token *token, t_data *data,
				int process_idx);
static char	*here_doc_process_line(char *s, t_data *data);
static char	*here_doc_get_env_var(char *s, t_data *data,
				t_here_doc_function *f);
static char	*here_doc_get_env_var_2(char *s, t_data *data,
				t_here_doc_function *f);

/*----------------------------------------------------------------------------*/

int	get_process_idx(t_process *proc, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->executor.process_amount)
	{
		if (data->executor.process_array[i] == proc)
			return (i);
	}
	return (-1);
}

/*	have to implement correct signals for the here_doc. Check how to do it. */
int	handle_redir_lesser_lesser_here_doc(t_token *token, t_data *data,
	int process_idx)
{
	char	*here_doc_str;

	while (1)
	{
		here_doc_str = readline("here_doc> ");
		if (ft_strncmp(here_doc_str, token->args[0],
				ft_strlen(here_doc_str)) == 0)
			break ;
		else
		{
			here_doc_str = here_doc_process_line(here_doc_str, data);
			ft_putendl_fd(here_doc_str, data->executor.here_doc_array
			[process_idx][T_PIPE_WRITE]);
		}
	}
	return (0);
}

static char	*here_doc_process_line(char *s, t_data *data)
{
	t_here_doc_function	f;

	f.str = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!f.str)
	{
		ft_putendl_fd("here_doc malloc failure", 2);
		return (NULL);
	}
	f.i = -1;
	while (s[++f.i])
	{
		if (s[f.i] == '$')
			f.str = here_doc_get_env_var(s, data, &f);
		else
			ft_strncat(f.str, s + f.i, 1);
	}
	free(s);
	return (f.str);
}

static char	*here_doc_get_env_var(char *s, t_data *data,
	t_here_doc_function *f)
{
	char	*result;

	if (s[f->i + 1] == '?')
	{
		f->i += 1;
		result = ft_itoa(data->latest_exit_status);
		f->str = (char *)ft_realloc(f->str, ft_strlen(s)
				+ 1 + ft_strlen(result));
		ft_strncat(f->str, result, ft_strlen(result));
		free(result);
	}
	else
		f->str = here_doc_get_env_var_2(s, data, f);
	return (f->str);
}

static char	*here_doc_get_env_var_2(char *s, t_data *data,
	t_here_doc_function *f)
{
	char	*result;
	char	*var_name;
	int		j;

	f->i++;
	j = f->i;
	while (ft_isalnum(s[j]) || s[j] == '_')
		j++;
	var_name = ft_calloc(j - f->i + 1, sizeof(char));
	if (!var_name)
	{
		f->i = j;
		ft_putendl_fd("here_doc_get_var malloc failure", 2);
		return (f->str);
	}
	ft_strncpy(var_name, s + f->i, j - f->i);
	f->i = j - 1;
	result = token_unpacker_get_var_from_env(var_name, data);
	if (!result)
		return (f->str);
	f->str = (char *)ft_realloc(f->str, ft_strlen(s)
			+ 1 + ft_strlen(result));
	ft_strncat(f->str, result, ft_strlen(result));
	free(result);
	return (f->str);
}
