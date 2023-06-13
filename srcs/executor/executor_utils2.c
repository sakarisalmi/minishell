/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:01:45 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/12 17:40:25 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"

int			executor_end_here_doc_ctrl_c(t_executor_function *f,
				t_executor *ex);
void		executor_start_allocation_failure_free(t_executor_function *f);
void		executor_start_print_redir_err_msgs(t_executor_function *f);
int			executor_start_malloc_f_vars(t_executor_function *f,
				int process_amount);

/*----------------------------------------------------------------------------*/

int	executor_end_here_doc_ctrl_c(t_executor_function *f, t_executor *ex)
{
	int	j;

	j = -1;
	(void)ex;
	if (f->pid)
		free(f->pid);
	if (f->result_fork)
		free(f->result_fork);
	if (f->result_redirs)
		free(f->result_redirs);
	return (1);
}

void	executor_start_allocation_failure_free(t_executor_function *f)
{
	if (f->redir_errs)
		free(f->redir_errs);
	if (f->result_fork)
		free(f->result_fork);
	if (f->result_redirs)
		free(f->result_redirs);
	if (f->pid)
		free(f->pid);
}

void	executor_start_print_redir_err_msgs(t_executor_function *f)
{
	int	i;

	i = -1;
	while (f->redir_errs[++i])
		ft_putendl_fd(f->redir_errs[i], 2);
	str_array_free_everything(f->redir_errs);
}

int	executor_start_malloc_f_vars(t_executor_function *f,
		int process_amount)
{
	f->redir_errs = ft_calloc(1, sizeof(char *));
	f->pid = ft_calloc(process_amount, sizeof(int));
	f->result_fork = ft_calloc(process_amount, sizeof(int));
	f->result_redirs = ft_calloc(process_amount, sizeof(int));
	if (!f->pid || !f->result_fork || !f->redir_errs || !f->result_redirs)
	{
		ft_putendl_fd("MINISHELL: executor: allocation failure", 2);
		executor_start_allocation_failure_free(f);
		return (1);
	}
	f->redir_errs[0] = NULL;
	return (0);
}
