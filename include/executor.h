/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:37:00 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/03 17:20:33 by ssalmi           ###   ########.fr       */
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

// executor.c
int		test_executor(t_data *data);

// job_utils1.c
t_job	**create_jobs_from_tokens(t_token *token_lst);
void	job_free_job(t_job *job);

// handle_redirs.c
int		job_handle_redirs(t_job *job, t_data *data);

// handle_redirs_utils1.c
int		handle_redir_greater(t_token *token);
int		handle_redir_greater_greater(t_token *token);
int		handle_redir_lesser(t_token *token);
int		handle_redir_lesser_lesser(t_token *token, t_data *data);

#endif