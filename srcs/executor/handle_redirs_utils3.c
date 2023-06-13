/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:16:20 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/13 13:35:19 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/tokenizer.h"
#include "../../include/executor.h"

void		here_doc_send_str_to_pipe(t_data *data, int process_idx, char *str);
int			handle_redirs_check_for_empty_filename(t_token *token,
				t_executor_function *f);
static char	*handle_redirs_ambiguous_redir_err_msg(char *rl_part);
int			handle_redirs_should_fd_be_closed(int fd, t_executor *ex);

/*----------------------------------------------------------------------------*/

void	here_doc_send_str_to_pipe(t_data *data, int process_idx, char *str)
{
	str = here_doc_process_line(str, data);
	write(data->executor.here_doc_array[process_idx][T_PIPE_WRITE],
		str, ft_strlen(str));
	write(data->executor.here_doc_array[process_idx][T_PIPE_WRITE],
		"\n", 1);
	free(str);
}

int	handle_redirs_check_for_empty_filename(t_token *token,
	t_executor_function *f)
{
	char	*rl_part;
	char	*error_msg;

	rl_part = token->next->rl_part_string;
	if (token->args[0][0] == '\0')
	{
		if (!ft_strchr(rl_part, '"'))
		{
			error_msg = handle_redirs_ambiguous_redir_err_msg(rl_part);
			f->redir_errs = str_array_add_str(f->redir_errs, error_msg);
		}
		else
		{
			error_msg = ft_strdup("MINISHELL: : failed to find or create file");
			f->redir_errs = str_array_add_str(f->redir_errs, error_msg);
		}
		return (1);
	}
	return (0);
}

static char	*handle_redirs_ambiguous_redir_err_msg(char *rl_part)
{
	char	*error_msg;

	error_msg = ft_calloc(32 + ft_strlen(rl_part), sizeof(char));
	if (error_msg)
	{
		ft_strncat(error_msg, "MINISHELL: ", ft_strlen("MINISHELL: "));
		ft_strncat(error_msg, rl_part, ft_strlen(rl_part));
		ft_strncat(error_msg, ": ambiguous redirect",
			ft_strlen(": ambiguous redirect"));
	}
	return (error_msg);
}

int	process_get_token_idx_in_proc(t_process *proc, t_token *token)
{
	int	i;

	i = 0;
	while (proc->tokens_array[i] != token)
		i++;
	return (i);
}

/*	this function is used when we want to find out should we close the
	previous fd_in or fd_out for a process. This function checks if
	the fd to close is from either a pipe between processes, a
	here_doc pipe, or if it is one of the STD_FILENOs. If the fd is from one of
	those we don't close the fd. If the fd is not from one of those pipes we
	know that the fd is for a file so we will close it!	*/
int	handle_redirs_should_fd_be_closed(int fd, t_executor *ex)
{
	int			i;

	if (fd == STDIN_FILENO || fd == STDOUT_FILENO)
		return (0);
	i = 0;
	while (i < ex->process_amount - 1)
	{
		if (fd == ex->fds_array[i][0] || fd == ex->fds_array[i][1])
			return (0);
		i++;
	}
	i = 0;
	while (i < ex->process_amount)
	{
		if (ex->here_doc_array[i])
		{
			if (ex->here_doc_array[i][0] || ex->here_doc_array[i][1])
				return (0);
		}
		i++;
	}
	return (1);
}
