/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:37:00 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/17 13:30:16 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "minishell.h"

enum e_stds
{
	T_STDIN,
	T_STDOUT,
	T_STDERR
};

enum e_PIPE_ENDS
{
	T_PIPE_READ,
	T_PIPE_WRITE
};

typedef struct s_here_doc_function
{
	char	*str;
	int		i;
}	t_here_doc_function;

typedef struct s_executor_function
{
	int	result;
	int	result_pid;
	int	*pid;
	int	i;
	int	j;
}	t_executor_function;

// executor.c
int		real_executor(t_executor *ex, t_data *data);
int		real_executor_pre_setup(t_data *data);

// job_utils1.c
t_job	**create_jobs_from_tokens(t_token *token_lst);
void	job_free_job(t_job *job);

// handle_redirs.c
int		job_handle_redirs(t_job *job, t_data *data);

// handle_redirs_utils1.c
int		handle_redir_greater(t_token *token);
int		handle_redir_greater_greater(t_token *token);
int		handle_redir_lesser(t_token *token);
int		handle_redir_lesser_lesser(t_token *token, t_job *job,
			t_data *data);

// handle_redirs_utils2.c
int		get_proc_idx(t_job *job, t_data *data);
int		handle_redir_lesser_lesser_here_doc(t_token *token, t_data *data,
			int process_idx);

// fds_array_utils1.c
int		executor_pipe_set_up(t_executor *exec);
void	close_pipe_ends_parent_process(int *fds);
int		**fds_array_create_fds_for_piping(int amount_of_jobs);
void	fds_array_free(int **fds_array, int free_until_idx);

// fds_array_utils2.c
void	close_all_pipe_fds(t_executor *exec);
int		**executor_set_up_here_doc_array(t_executor *exec);
int		executor_set_up_here_doc_pipe(t_executor *exec, int idx);

// executor_cmd_utils1.c
t_token	*job_get_cmd_token(t_job *job);
char	*find_cmd_path(char *cmd, char **env);

// executor_utils1.c
void	executor_start(t_executor_function *f, t_executor *ex);
int		executor_end(t_executor_function *f, t_executor *ex);
int		executor_check_if_to_fork(t_executor_function *f,
			t_executor *ex, t_data *data);
int		executor_error_msg(char *s, int error_code);

// executor_clean_up.c
void	executor_clean_up(t_data *data, int jobs_amount);

#endif