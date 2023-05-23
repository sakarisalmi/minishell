/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:01:45 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/23 18:23:59 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"

int			executor_end_here_doc_ctrl_c(t_executor_function *f,
				t_executor *ex);
// static void	executor_end_here_doc_close_all(t_executor *ex);
void		executor_start_allocation_failure_free(t_executor_function *f);
void		executor_start_print_redir_err_msgs(t_executor_function *f);

/*----------------------------------------------------------------------------*/

int	executor_end_here_doc_ctrl_c(t_executor_function *f, t_executor *ex)
{
	int	j;

	j = -1;
	(void)ex;
	free(f->pid);
	free(f->result_new);
	return (1);
}

// static void	executor_end_here_doc_close_all(t_executor *ex)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < ex->process_amount)
// 	{
// 		if (i != 0)
// 		{
// 			close(ex->fds_array[i - 1][0]);
// 			close(ex->fds_array[i - 1][1]);
// 		}
// 		close(ex->here_doc_array[i][0]);
// 		close(ex->here_doc_array[i][1]);
// 	}
// }

void	executor_start_allocation_failure_free(t_executor_function *f)
{
	if (f->redir_errs)
		free(f->redir_errs);
	if (f->result_new)
		free(f->result_new);
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
