/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:28:16 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/23 17:36:31 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"
#include "../../include/executor.h"
#include "../../include/builtin.h"

int			handle_redir_greater(t_token *token, t_executor_function *f);
int			handle_redir_greater_greater(t_token *token,
				t_executor_function *f);
int			handle_redir_lesser(t_token *token, t_executor_function *f);
int			handle_redir_lesser_lesser(t_token *token, t_process *proc,
				t_data *data);

/*----------------------------------------------------------------------------*/

int	handle_redir_greater(t_token *token, t_executor_function *f)
{
	int		result;
	char	*err_msg;

	result = open(token->args[0], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (result < 0)
	{
		err_msg = ft_calloc(43 * ft_strlen(token->args[0]), sizeof(char));
		if (!err_msg)
		{
			ft_putendl_fd("MINISHELL: handle_redir malloc failure", 2);
			return (result);
		}
		ft_strncat(err_msg, "MINISHELL: ", ft_strlen("MINISHELL: "));
		ft_strncat(err_msg, token->args[0], ft_strlen(token->args[0]));
		ft_strncat(err_msg, ": failed to find or create file",
			ft_strlen(": failed to find or create file"));
		f->redir_errs = str_array_add_str(f->redir_errs, err_msg);
	}
	return (result);
}

int	handle_redir_greater_greater(t_token *token, t_executor_function *f)
{
	int		result;
	char	*err_msg;

	result = open(token->args[0], O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (result < 0)
	{
		err_msg = ft_calloc(43 * ft_strlen(token->args[0]), sizeof(char));
		if (!err_msg)
		{
			ft_putendl_fd("MINISHELL: handle_redir malloc failure", 2);
			return (result);
		}
		ft_strncat(err_msg, "MINISHELL: ", ft_strlen("MINISHELL: "));
		ft_strncat(err_msg, token->args[0], ft_strlen(token->args[0]));
		ft_strncat(err_msg, ": failed to find or create file",
			ft_strlen(": failed to find or create file"));
		f->redir_errs = str_array_add_str(f->redir_errs, err_msg);
	}
	return (result);
}

int	handle_redir_lesser(t_token *token, t_executor_function *f)
{
	int		result;
	char	*err_msg;

	result = open(token->args[0], O_RDONLY);
	if (result < 0)
	{
		err_msg = ft_calloc(39 + ft_strlen(token->args[0]), sizeof(char));
		if (!err_msg)
		{
			ft_putendl_fd("MINISHELL: handle_redir malloc failure", 2);
			return (result);
		}
		ft_strncat(err_msg, "MINISHELL: ", ft_strlen("MINISHELL: "));
		ft_strncat(err_msg, token->args[0], ft_strlen(token->args[0]));
		ft_strncat(err_msg, ": No such file or directory",
			ft_strlen(": No such file or directory"));
		f->redir_errs = str_array_add_str(f->redir_errs, err_msg);
	}
	return (result);
}

/*	Do later! how do you do the here_doc, check for examples!*/
int	handle_redir_lesser_lesser(t_token *token, t_process *proc, t_data *data)
{
	int		process_idx;
	int		result;

	process_idx = get_process_idx(proc, data);
	if (process_idx == -1)
		return (-1);
	result = handle_redir_lesser_lesser_here_doc(token, data, process_idx);
	if (result == 1)
		return (-42);
	return (data->executor.here_doc_array[process_idx][T_PIPE_READ]);
}
