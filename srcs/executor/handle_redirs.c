/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:26:18 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/13 13:42:04 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"
#include "../../include/executor.h"

int			job_handle_redirs(t_data *data, t_executor_function *f);
static int	process_handle_redirs_first_loop(t_process *proc, t_data *data);
static int	process_handle_redirs_second_loop(t_process *proc,
				t_executor_function *f, t_data *data);
static int	process_handle_redirs_just_lesser(t_process *proc, int idx,
				t_executor_function *f);
static int	process_handle_redirs_greaters(t_process *proc, int idx,
				t_executor_function *f, t_data *data);

/*----------------------------------------------------------------------------*/

/*	This function handles the job's redirection. First we loop through all
	the processes and handles the lesser lesser (here_doc) redirections.
	If this is successful we loop through the processes again and handle
	the other redirections.
	This function will return a non-zero value if during the here_doc ctrl-c
	is pressed.	*/
int	job_handle_redirs(t_data *data, t_executor_function *f)
{
	int			result;
	t_executor	*ex;

	ex = &data->executor;
	f->i = -1;
	while (++f->i < data->executor.process_amount)
	{
		printf("in job_handle_redirs; proc: %d\n", f->i);
		result = process_handle_redirs_first_loop(ex->process_array[f->i],
				data);
		if (result == -42)
			return (result);
	}
	f->i = -1;
	while (++f->i < data->executor.process_amount)
	{
		result = process_handle_redirs_second_loop(ex->process_array[f->i], f, data);
		if (result < 0)
		{
			f->result_redirs[f->i] = result;
			continue ;
		}
	}
	f->i = -1;
	return (0);
}

/*	This function handles a process's lesser_lesser redirections. If the
	user presses ctrl-c during the here_doc, The whole job will be aborted. */
static int	process_handle_redirs_first_loop(t_process *proc, t_data *data)
{
	int	latest_result;
	int	i;

	latest_result = 0;
	i = -1;
	while (proc->tokens_array[++i])
	{
		if (proc->tokens_array[i]->type == T_REDIR
			&& ft_strncmp(proc->tokens_array[i]->string, "<<", 3) == 0)
		{
			if (executor_set_up_here_doc_pipe(&data->executor,
					get_process_idx(proc, data)) != 0)
				return (-1);
			latest_result = handle_redir_lesser_lesser(
					proc->tokens_array[i], proc, data);
			if (latest_result < 0)
				return (latest_result);
			proc->last_here_doc = process_get_token_idx_in_proc(proc,
					proc->tokens_array[i]);
			proc->fd_in = latest_result;
		}
	}
	return (0);
}

/*	This function handles a proc's redirections. It will iterate
	through all of the tokens, and handle all of the redirections
	(except lesser_lesser), constantly updating the stdin and stdout
	with the latest redirs.
	If the redir fails (let's say the infile doesn't exist), this
	function will return a value under zero, after which stop the proc
	and set exit status */
static int	process_handle_redirs_second_loop(t_process *proc,
	t_executor_function *f, t_data *data)
{
	int	result;
	int	i;

	result = 0;
	i = -1;
	while (proc->tokens_array[++i])
	{
		if (proc->tokens_array[i]->type == T_REDIR
			&& ft_strncmp(proc->tokens_array[i]->string, "<<", 3) != 0)
		{
			if (proc->tokens_array[i]->string[0] == '<')
				result = process_handle_redirs_just_lesser(
						proc, i, f);
			else
				result = process_handle_redirs_greaters(proc, i, f, data);
		}
		if (result < 0)
			return (result);
	}
	return (0);
}

static int	process_handle_redirs_just_lesser(t_process *proc, int idx,
	t_executor_function *f)
{
	int	result;

	result = handle_redir_lesser(proc->tokens_array[idx], f);
	if (result < 0)
		return (result);
	if (idx > proc->last_here_doc)
	{
		if (proc->fd_in != STDIN_FILENO && proc->fd_in != result)
			close(proc->fd_in);
		proc->fd_in = result;
	}
	else
		close(result);
	return (0);
}

int isFileDescriptorOpen2(int fd) {
    int flags = fcntl(fd, F_GETFL);
    return (flags != -1);
}

static int	process_handle_redirs_greaters(t_process *proc, int idx,
	t_executor_function *f, t_data *data)
{
	int	result;

	result = -42;
	printf("\t\tin process_handle_redirs_greaters; proc[%d]\n", get_process_idx(proc, data));
	if (ft_strncmp(proc->tokens_array[idx]->string, ">", 2) == 0)
		result = handle_redir_greater(proc->tokens_array[idx], f);
	else
		result = handle_redir_greater_greater(proc->tokens_array[idx], f);
	printf("\t\tgreaters; proc[%d]: result: %d\n", get_process_idx(proc, data), result);
	if (result < 0)
		return (result);
	if (handle_redirs_should_fd_be_closed(proc->fd_out, &data->executor))
	{
		printf("proc[%d]: handle_redirs_should_fd_be_closed; closing old fd_out (%d)\n", get_process_idx(proc, data), proc->fd_out);
		close(proc->fd_out);
	}
	else
		printf("proc[%d]: handle_redirs_should_fd_be_closed; NOT closing old fd_out (%d)\n", get_process_idx(proc, data), proc->fd_out);
	// if (proc->fd_out != STDOUT_FILENO && proc->fd_out != result)
	// {
	// 	printf("\t\tgreaters; proc[%d] closing old fd_out: num: %d\n", get_process_idx(proc, data), proc->fd_out);
	// 	close(proc->fd_out);
	// }
	// else
	// 	printf("\t\tgreaters; proc[%d] did not close old fd_out!\n", get_process_idx(proc, data));
	proc->fd_out = result;
	// if (isFileDescriptorOpen2(proc->fd_out))
	// 	printf("\t\t\tproc[%d] FD_OUT IS OPEN!\n", get_process_idx(proc, data));
	// else
	// 	printf("\t\t\tproc[%d] FD_OUT IS NOT OPEN!\n", get_process_idx(proc, data));
	return (0);
}
