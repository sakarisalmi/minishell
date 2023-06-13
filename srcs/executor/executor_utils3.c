/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:45:44 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/13 13:50:05 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/builtin.h"

void		executor_close_proc_fds(t_process *proc);
int			executor_find_and_exec_builtin(t_process *proc, t_data *data);
int			executor_exec_single_builtin_proc(t_process *proc, t_data *data);
static void	executor_single_builtin_proc_return_orig_fds(int in, int out);

/*----------------------------------------------------------------------------*/

void	executor_close_proc_fds(t_process *proc)
{
	if (proc->fd_in != STDIN_FILENO)
		close(proc->fd_in);
	if (proc->fd_out != STDOUT_FILENO)
		close(proc->fd_out);
}

int	executor_find_and_exec_builtin(t_process *proc, t_data *data)
{
	t_token	*builtin_token;

	builtin_token = process_get_cmd_token(proc);
	if (!ft_strncmp_casein(builtin_token->string, "cd", 3))
		return (cd(builtin_token->args, data));
	if (!ft_strncmp_casein(builtin_token->string, "echo", 5))
		return (echo(builtin_token->args));
	if (!ft_strncmp_casein(builtin_token->string, "pwd", 4))
		return (pwd());
	if (!ft_strncmp_casein(builtin_token->string, "export", 7))
		return (export(builtin_token->args, data));
	if (!ft_strncmp_casein(builtin_token->string, "unset", 6))
		return (unset(builtin_token->args, data));
	if (!ft_strncmp_casein(builtin_token->string, "env", 4))
		return (env(builtin_token->args, data));
	if (!ft_strncmp_casein(builtin_token->string, "exit", 5))
		return (minishell_exit(builtin_token->args, data));
	return (0);
}

int	executor_exec_single_builtin_proc(t_process *proc, t_data *data)
{
	int	in;
	int	out;
	int	result;

	in = -42;
	out = -42;
	if (proc->fd_in != STDIN_FILENO)
	{
		in = dup(0);
		dup2(proc->fd_in, 0);
		close(proc->fd_in);
	}
	if (proc->fd_out != STDOUT_FILENO)
	{
		out = dup(1);
		dup2(proc->fd_out, 1);
		close(proc->fd_out);
	}
	result = executor_find_and_exec_builtin(proc, data);
	executor_single_builtin_proc_return_orig_fds(in, out);
	return (result);
}

static void	executor_single_builtin_proc_return_orig_fds(int in, int out)
{
	if (in != -42)
	{
		dup2(in, 0);
		close(in);
	}
	if (out != -42)
	{
		dup2(out, 1);
		close(out);
	}
}
