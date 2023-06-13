/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 11:00:35 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/12 19:05:48 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/tokenizer.h"
#include "../../include/builtin.h"

//remove later
#include <fcntl.h>



static int		executor(t_executor *ex, t_data *data);
int				executor_pre_setup(t_data *data);
static int		executor_single_builtin_process(t_executor *ex, t_data *data);
static int		executor_builtin_func(t_process *proc, t_data *data);
static void		executor_exec_cmd(t_process *proc, t_data *data);

/*----------------------------------------------------------------------------*/

static int	executor(t_executor *ex, t_data *data)
{
	t_executor_function	f;

	if (executor_start(&f, ex, data) != 0)
		return (executor_end_here_doc_ctrl_c(&f, ex));
	while (++f.i < ex->process_amount)
	{
		if (f.result_fork[f.i] == 0)
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
		}
		executor_close_proc_fds(ex->process_array[f.i]);
		close_pipe_ends_parent_process(ex->here_doc_array[f.i]);
		if (f.i != 0)
			close_pipe_ends_parent_process(ex->fds_array[f.i - 1]);
	}
	return (executor_end(&f, ex));
}

int	executor_pre_setup(t_data *data)
{
	int	i;

	data->executor.token_lst = data->parser.token_lst;
	data->executor.process_array = create_processes_from_tokens(
			data->executor.token_lst, data);
	i = 0;
	while (data->executor.process_array[i])
		i++;
	data->executor.process_amount = i;
	data->executor.here_doc_array = \
		executor_set_up_here_doc_array(&data->executor);
	if (!data->executor.here_doc_array)
		minishell_fatal_error_exit(data);
	if (data->executor.process_amount == 1
		&& check_for_builtin(data->executor.process_array[0]->tokens_array))
		return (executor_single_builtin_process(&data->executor, data));
	else
	{
		if (data->executor.process_amount > 1)
			if (executor_pipe_set_up(&data->executor) != 0)
				return (executor_error_msg(NULL, 2));
		return (executor(&data->executor, data));
	}
	return (0);
}

/*	This function handles the execution of the read_line when there is only
	a single proc and the command in it is a built-in. We do this to not to
	fork, which happens otherwise in the normal execution of commands	.*/
static int	executor_single_builtin_process(t_executor *ex, t_data *data)
{
	int					result;
	t_executor_function	f;

	printf("in executor_single_builtint_process\n");
	if (executor_start(&f, ex, data) != 0)
		return (executor_end_here_doc_ctrl_c(&f, ex));
	printf("executor_single_builtint_process; stage 1\n");
	result = f.result_fork[0];
	free(f.pid);
	free(f.result_fork);
	free(f.result_redirs);
	printf("executor_single_builtint_process; stage 2\n");
	if (result != 0)
		return (result);
	else
		return (executor_exec_single_builtin_proc(ex->process_array[0], data));
}

/*	This function is used when there is more than one process to execute. That
	means this process was forked. If there is just one process in a job and that
	process is a builtin, we use the function executor_single_builtin_process.*/
static int	executor_builtin_func(t_process *proc, t_data *data)
{
	int	dup_result;

	printf("\tproc[%d] executor_builtin_func\n", get_process_idx(proc, data));
	if (proc->fd_in != STDIN_FILENO)
	{
		printf("\tproc[%d] fd_in: %d\n", get_process_idx(proc, data), proc->fd_in);
		dup_result = dup2(proc->fd_in, STDIN_FILENO);
		printf("\tproc[%d] executor_builtin_func; dup2 fd_in result: %d\n", get_process_idx(proc, data), dup_result);
		close(proc->fd_in);
	}
	if (proc->fd_out != STDOUT_FILENO)
	{
		printf("\tproc[%d] fd_out: %d\n", get_process_idx(proc, data), proc->fd_out);
		dup_result = dup2(proc->fd_out, STDOUT_FILENO);
		printf("\tproc[%d] executor_builtin_func; dup2 fd_out result: %d\n", get_process_idx(proc, data), dup_result);
		close(proc->fd_out);
	}
	close_all_pipe_fds(&data->executor);
	return (executor_find_and_exec_builtin(proc, data));
}

/*	this is the function the child process will go into to execute the proc.
	First we check if the proc's fd_in or fd_out are not the STDIN r STDOUT
	and if so, we will dup2 the fds. We will then check if there is a command
	in the proc and if so, we will execve the command. If there is no command,
	we will exit the process with zero. 
	HUOM: what to do about built-ins? will prob have to go in another func
	(this functions line amount is close to the limit)*/

int isFileDescriptorOpen(int fd) {
    int flags = fcntl(fd, F_GETFL);
    return (flags != -1);
}

static void	executor_exec_cmd(t_process *proc, t_data *data)
{
	t_token	*cmd_token;
	int		proc_idx;
	int		dup_result;

	proc_idx = get_process_idx(proc, data);
	dprintf(2, "EXECUTOR proc[%d] fd_in: %d\n", proc_idx, proc->fd_in);
	if (isFileDescriptorOpen(proc->fd_in)) {
        printf("proc[%d]: fd_in is open.\n", proc_idx);
    } else {
        printf("proc[%d]fd_in is not open.\n", proc_idx);
    }
	if (isFileDescriptorOpen(proc->fd_out)) {
        printf("proc[%d]; fd_out is open.\n", proc_idx);
    } else {
        printf("proc[%d]; fd_out is not open.\n", proc_idx);
    }
	dprintf(2, "EXECUTOR proc[%d] fd_out: %d\n", proc_idx, proc->fd_out);
	if (proc->fd_in != STDIN_FILENO)
	{
		dprintf(2, "proc[%d] dupping fd_in: %d\n", proc_idx, proc->fd_in);
		dup_result = dup2(proc->fd_in, STDIN_FILENO);
		dprintf(2, "proc[%d] result of fd_in dup: %d\n", proc_idx, dup_result);
		if (dup_result == -1)
			perror("\t\t\033[0;31mdup failure reason\033[0;37m");
		close(proc->fd_in);
	}
	if (proc->fd_out != STDOUT_FILENO)
	{
		dprintf(2, "proc[%d] dupping fd_out: %d\n", proc_idx, proc->fd_out);
		dup_result = dup2(proc->fd_out, STDOUT_FILENO);
		dprintf(2, "proc[%d] result of fd_out dup: %d\n", proc_idx, dup_result);
		if (dup_result == -1)
			perror("\t\t\033[0;31mdup failure reason\033[0;37m");
		close(proc->fd_out);
	}
	close_all_pipe_fds(&data->executor);
	cmd_token = process_get_cmd_token(proc);
	if (proc->cmd_path)
	{
		if (execve(proc->cmd_path, cmd_token->args, data->envs) < 0)
			exit(executor_error_msg(NULL, 3));
	}
	exit(0);
}
