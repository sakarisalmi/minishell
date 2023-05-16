/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 16:06:06 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/16 15:18:00 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/tokenizer.h"
#include "../../include/executor.h"

int	handle_redir_lesser_lesser_get_proc_idx(t_token *token,
	t_data *data)
{
	int	idx;
	int	i;

	idx = -1;
	while (++idx < data->executor.jobs_amount)
	{
		i = -1;
		while (data->executor.jobs_array[idx]->tokens_array[++i])
			if (token == data->executor.jobs_array[idx]->tokens_array[i])
				return (idx);
	}
	return (-1);
}

/*	have to implement correct signals for the here_doc. Check how to do it. */
void	handle_redir_lesser_lesser_here_doc(t_token *token, t_data *data)
{
	char	*here_doc_str;

	while (1)
	{
		here_doc_str = readline("here_doc> ");
		if (ft_strncmp(here_doc_str, token->args[0],
				ft_strlen(token->args[0])) == 0)
			break ;
		else
		{
			printf("%s", here_doc_str);
		}
	}
}

static char	*here_doc_process_line(char *s, t_data *data)
{
	t_here_doc_function	f;

	f.str1 = ft_calloc(ft_strlen(s), sizeof(char));
	if (!f.str1)
	{
		ft_putendl_fd("here_doc malloc failure", 2);
		return (NULL);
	}
	f.i = -1;
	f.j = -1;
	while (s[++f.i])
	{
		if (s[f.i] == '$')
			f.str1 = here_doc_get_env_var(s, data, &f);
		else
			ft_strncat(f.str1, s + f.i, 1);
	}
	return (f.str1);
}

static char	*here_doc_get_env_var(char *s, t_data *data,
	t_here_doc_function *f)
{
	char	*result;

	if (s[f->i + 1] == '?')
	{
		f->i += 2;
		result = ft_itoa(data->latest_exit_status);
		f->str1 = (char *)ft_realloc(f->str1, ft_strlen(s) + ft_strlen(result));
		ft_strncat(f->str1, result, ft_strlen(result));
		free(result);
	}
	else
		f->str1 = here_doc_get_env_var_2(s, data, f);
	return (f->str1);
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
	var_name = ft_calloc(j - f->i, sizeof(char));
	if (!var_name)
	{
		f->i = j;
		ft_putendl_fd("here_doc_get_var malloc failure", 2);
		return (f->str1);
	}
	ft_strncpy(var_name, s + f->i, j - f->i);
	f->i = j;
	result = token_unpacker_get_var_from_env(var_name, data);
	if (!result)
		return (f->str1);
	f->str1 = (char *)ft_realloc(f->str1, ft_strlen(s) + ft_strlen(result));
	ft_strncat(f->str1, result, ft_strlen(result));
	free(result);
	return (f->str1);
}
