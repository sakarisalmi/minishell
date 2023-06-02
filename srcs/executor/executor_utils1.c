/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:34:35 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/25 13:23:06 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/tokenizer.h"
#include "../../include/builtin.h"

int			executor_start(t_executor_function *f, t_executor *ex,
				t_data *data);
int			executor_end(t_executor_function *f, t_executor *ex);
int			executor_check_if_to_fork(t_executor_function *f, t_executor *ex,
				t_data *data);
static int	executor_check_if_path_is_dir(t_token *token_cmd);
int			executor_error_msg(char *s, int error_code);

/*----------------------------------------------------------------------------*/

int	executor_start(t_executor_function *f, t_executor *ex, t_data *data)
{
	int	redirs_result;

	f->i = -1;
	f->j = -1;
	if (executor_start_malloc_f_vars(f, ex->process_amount) != 0)
		return (-1);
	redirs_result = job_handle_redirs(data, f);
	executor_start_print_redir_err_msgs(f);
	if (redirs_result == -42)
		return (1);
	while (++f->i < ex->process_amount)
		f->result_fork[f->i] = executor_check_if_to_fork(f, ex, data);
	f->i = -1;
	return (0);
}

// int	executor_start(t_executor_function *f, t_executor *ex, t_data *data)
// {
// 	f->i = -1;
// 	f->j = -1;
// 	if (executor_start_malloc_f_vars(f, ex->process_amount) != 0)
// 		return (-1);
// 	while (++f->i < ex->process_amount)
// 	{
// 		f->result_fork[f->i] = executor_check_if_to_fork(f, ex, data);
// 		if (f->result_fork[f->i] == -42)
// 		{
// 			str_array_free_everything(f->redir_errs);
// 			return (1);
// 		}
// 	}
// 	executor_start_print_redir_err_msgs(f);
// 	f->i = -1;
// 	return (0);
// }

int	executor_end(t_executor_function *f, t_executor *ex)
{
	int	latest_result;

	while (++f->j < ex->process_amount)
		waitpid(f->pid[f->j], &f->result_pid, 0);
	free(f->pid);
	f->pid = NULL;
	latest_result = f->result_fork[ex->process_amount - 1];
	free(f->result_redirs);
	free(f->result_fork);
	if (latest_result != 0)
		return (latest_result);
	else
	{
		if (WIFEXITED(f->result_pid))
			return (WEXITSTATUS(f->result_pid));
		if (WIFSIGNALED(f->result_pid))
		{
			if (WTERMSIG(f->result_pid) == SIGQUIT)
				write(1, "Quit: 3", 8);
			write(1, "\n", 1);
			return (WTERMSIG(f->result_pid) + 128);
		}
		return (0);
	}
}

/*	This function will be used before forking to check if the fork is needed.*/
int	executor_check_if_to_fork(t_executor_function *f, t_executor *ex,
	t_data *data)
{
	t_token	*cmd_token;

	if (f->result_redirs[f->i] != 0)
		return (f->result_redirs[f->i]);
	if (check_for_builtin(ex->process_array[f->i]->tokens_array))
		return (0);
	cmd_token = process_get_cmd_token(ex->process_array[f->i]);
	if (cmd_token)
	{
		if (cmd_token->string[0] == '\0')
			return (executor_error_msg(cmd_token->string, 4));
		ex->process_array[f->i]->cmd_path = find_cmd_path(cmd_token->string,
				data->envs);
		if (!ex->process_array[f->i]->cmd_path)
			return (executor_error_msg(cmd_token->string, 4));
		else
			return (executor_check_if_path_is_dir(cmd_token));
	}
	else
		return (0);
}

static int	executor_check_if_path_is_dir(t_token *cmd_token)
{
	char	current_dir[4096];
	char	error_msg[4096];

	ft_bzero(current_dir, 4096);
	ft_bzero(error_msg, 4096);
	if (getcwd(current_dir, 4096) == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
	if (chdir(cmd_token->string) == 0)
	{
		chdir(current_dir);
		ft_strncat(error_msg, "MINISHELL: ", ft_strlen("MINISHELL: "));
		ft_strncat(error_msg, cmd_token->string, ft_strlen(cmd_token->string));
		ft_strncat(error_msg, ": is a directory",
			ft_strlen(": is a directory"));
		ft_putendl_fd(error_msg, 2);
		return (126);
	}
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
		exit(126);
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
