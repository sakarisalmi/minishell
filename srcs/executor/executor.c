/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:00:35 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/18 16:25:54 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/tokenizer.h"
#include "../../include/builtin.h"

static int		executor(t_executor *ex, t_data *data);
int				executor_pre_setup(t_data *data);
static int		executor_single_builtin_process(t_executor *ex, t_data *data);
static int		executor_builtin_func(t_process *proc, t_data *data);
static void		executor_exec_cmd(t_process *proc, t_data *data);

/*----------------------------------------------------------------------------*/

static int	executor(t_executor *ex, t_data *data)
{
	t_executor_function	f;

	executor_start(&f, ex);
	while (++f.i < ex->process_amount)
	{
		f.result = executor_check_if_to_fork(&f, ex, data);
		if (f.result == 0)
		{
			f.pid[f.i] = fork();
			if (f.pid[f.i] == 0)
			{
				if (check_for_builtin(ex->process_array[f.i]->tokens_array))
					exit(executor_builtin_func(ex->process_array[f.i], data));
				executor_exec_cmd(ex->process_array[f.i], data);
			}
			else if (f.pid[f.i] < 0)
				return (executor_error_msg(NULL, 1));
			close_pipe_ends_parent_process(ex->here_doc_array[f.i]);
			if (f.i != 0)
				close_pipe_ends_parent_process(ex->fds_array[f.i - 1]);
		}
		else
			break ;
	}
	return (executor_end(&f, ex));
}

int	executor_pre_setup(t_data *data)
{
	int	i;

	data->executor.token_lst = data->parser.token_lst;
	data->executor.process_array = create_processes_from_tokens(
			data->executor.token_lst);
	i = 0;
	while (data->executor.process_array[i])
		i++;
	data->executor.process_amount = i;
	data->executor.here_doc_array = \
		executor_set_up_here_doc_array(&data->executor);
	if (data->executor.process_amount == 1
		&& check_for_builtin(data->executor.process_array[0]->tokens_array))
		return (executor_single_builtin_process(&data->executor, data));
	else
	{
		if (data->executor.process_amount > 1)
		{
			if (executor_pipe_set_up(&data->executor) != 0)
				return (executor_error_msg(NULL, 2));
		}
		return (executor(&data->executor, data));
	}
	return (0);
}

/*	This function handles the execution of the read_line when there is only
	a single proc and the command in it is a built-in. We do this to not to
	fork, which happens otherwise in the normal execution of commands	.*/
static int	executor_single_builtin_process(t_executor *ex, t_data *data)
{
	int	result;

	result = process_handle_redirs(ex->process_array[0], data);
	if (result != 0)
		return (result);
	return (executor_builtin_func(ex->process_array[0], data));
}

static int	executor_builtin_func(t_process *proc, t_data *data)
{
	t_token	*builtin_token;

	if (proc->fd_in != STDIN_FILENO)
		dup2(proc->fd_in, STDIN_FILENO);
	if (proc->fd_out != STDOUT_FILENO)
		dup2(proc->fd_out, STDOUT_FILENO);
	close_all_pipe_fds(&data->executor);
	builtin_token = process_get_cmd_token(proc);
	if (ft_strncmp_casein(builtin_token->string, "cd", 3))
		return (cd(builtin_token->args, data));
	if (ft_strncmp_casein(builtin_token->string, "echo", 5))
		return (echo(builtin_token->args));
	if (ft_strncmp_casein(builtin_token->string, "pwd", 4))
		return (pwd());
	if (ft_strncmp_casein(builtin_token->string, "export", 7))
		return (export(builtin_token->args, data));
	if (ft_strncmp_casein(builtin_token->string, "unset", 6))
		return (unset(builtin_token->args));
	if (ft_strncmp_casein(builtin_token->string, "env", 4))
		return (env(data));
	if (ft_strncmp_casein(builtin_token->string, "exit", 5))
		return (minishell_exit(data));
	return (0);
}

/*	this is the function the child process will go into to execute the proc.
	First we check if the proc's fd_in or fd_out are not the STDIN r STDOUT
	and if so, we will dup2 the fds. We will then check if there is a command
	in the proc and if so, we will execve the command. If there is no command,
	we will exit the process with zero. 
	HUOM: what to do about built-ins? will prob have to go in another func
	(this functions line amount is close to the limit)*/
static void	executor_exec_cmd(t_process *proc, t_data *data)
{
	t_token	*cmd_token;

	if (proc->fd_in != STDIN_FILENO)
		dup2(proc->fd_in, STDIN_FILENO);
	if (proc->fd_out != STDOUT_FILENO)
		dup2(proc->fd_out, STDOUT_FILENO);
	close_all_pipe_fds(&data->executor);
	cmd_token = process_get_cmd_token(proc);
	if (proc->cmd_path)
	{
		if (execve(proc->cmd_path, cmd_token->args, data->envs) < 0)
			exit(executor_error_msg(NULL, 3));
	}
	exit(0);
}
