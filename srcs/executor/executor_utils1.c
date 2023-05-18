/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:34:35 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/16 17:01:55 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/tokenizer.h"

void	executor_start(t_executor_function *f, t_executor *ex);
int		executor_end(t_executor_function *f, t_executor *ex);
int		executor_check_if_to_fork(t_executor_function *f, t_executor *ex,
			t_data *data);
int		executor_error_msg(char *s, int error_code);

/*----------------------------------------------------------------------------*/

void	executor_start(t_executor_function *f, t_executor *ex)
{
	f->i = -1;
	f->j = -1;
	f->pid = NULL;
	f->pid = ft_calloc(ex->jobs_amount, sizeof(int));
	if (!f->pid)
	{
		ft_putendl_fd("MINISHELL: executor: pid(s) allocation failed", 2);
		return ;
	}
}

int	executor_end(t_executor_function *f, t_executor *ex)
{
	while (++f->j < ex->jobs_amount)
		waitpid(f->pid[f->j], &f->result_pid, 0);
	free(f->pid);
	f->pid = NULL;
	if (f->result != 0)
		return (f->result);
	else
	{
		if (WIFEXITED(f->result_pid))
			return (WEXITSTATUS(f->result_pid));
		if (WIFSIGNALED(f->result_pid))
			return (WTERMSIG(f->result_pid));
		return (0);
	}
}

/*	This function will be used before forking to check if the fork is needed.*/
int	executor_check_if_to_fork(t_executor_function *f, t_executor *ex,
	t_data *data)
{
	t_token	*cmd_token;
	int		result;

	result = 0;
	f->result = job_handle_redirs(ex->jobs_array[f->i], data);
	if (result != 0)
		return (result);
	if (check_for_builtin(ex->jobs_array[f->i]->tokens_array))
		return (0);
	cmd_token = job_get_cmd_token(ex->jobs_array[f->i]);
	if (cmd_token)
	{
		ex->jobs_array[f->i]->cmd_path = find_cmd_path(cmd_token->string,
				data->envs);
		if (!ex->jobs_array[f->i]->cmd_path)
			return (executor_error_msg(cmd_token->string, 4));
		else
			return (0);
	}
	else
		return (0);
}

/*	This function handle's printing out the error message that happen in
	the executor; done to save precious space in other functions.
	The error code tells the function what error message to print and
	what to return.
	Error codes:
	1. fork failure
	2. executor_pipe_set_up failure
	3. execve failure
	4. command not found	*/
int	executor_error_msg(char *s, int error_code)
{
	if (error_code == 1)
	{
		perror("MINISHELL: fork");
		return (-1);
	}
	if (error_code == 2)
	{
		ft_putendl_fd("MINISHELL: executor_pipe_set_up failure", 2);
		return (-1);
	}
	if (error_code == 3)
	{
		perror("MINISHELL: execve");
		exit(-1);
	}
	if (error_code == 4)
	{
		ft_putstr_fd("MINISHELL: ", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd(": command not found", 2);
		return (127);
	}
	return (0);
}
