/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_array_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:32:58 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/08 18:00:58 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"

void		close_all_pipe_fds(t_executor *exec);
int			**executor_set_up_here_doc_array(t_executor *exec);
static int	**executor_create_here_doc_array(t_executor *exec);
int			executor_set_up_here_doc_pipe(t_executor *exec, int idx);

/*----------------------------------------------------------------------------*/

void	close_all_pipe_fds(t_executor *exec)
{
	int	i;

	dprintf(2, "\tin close all pipe fds; proc amount: %d\n", exec->process_amount);
	i = -1;
	if (exec->fds_array)
	{
		while (++i < exec->process_amount - 1)
		{
			close(exec->fds_array[i][0]);
			close(exec->fds_array[i][1]);
		}
	}
	i = -1;
	while (++i < exec->process_amount)
	{
		dprintf(2, "\tlooping here_doc[%d]\n", i);
		if (exec->here_doc_array[i])
		{
			dprintf(2, "\tclosing here_doc_array[%d] pipe ends\n", i);
			close(exec->here_doc_array[i][0]);
			close(exec->here_doc_array[i][1]);
		}
	}
	dprintf(2, "\tend of close all pipe fds\n");
}

int	**executor_set_up_here_doc_array(t_executor *exec)
{
	int	**here_doc_array;

	here_doc_array = executor_create_here_doc_array(exec);
	if (!here_doc_array)
		return (NULL);
	return (here_doc_array);
}

static int	**executor_create_here_doc_array(t_executor *exec)
{
	int	**here_doc_array;
	int	i;

	here_doc_array = ft_calloc(exec->process_amount, sizeof(int *));
	if (!here_doc_array)
	{
		ft_putendl_fd("MINISHELL: error: here_doc_array alloc failure", 2);
		return (NULL);
	}
	i = -1;
	while (++i < exec->process_amount)
		here_doc_array[i] = NULL;
	return (here_doc_array);
}

int	executor_set_up_here_doc_pipe(t_executor *exec,
	int idx)
{
	printf("\nin executor_set_up_here_doc_pipe: idx: %d\n", idx);
	if (exec->here_doc_array[idx])
	{
		printf("closing prev here_doc\n");
		close(exec->here_doc_array[idx][T_PIPE_READ]);
		close(exec->here_doc_array[idx][T_PIPE_WRITE]);
		free(exec->here_doc_array[idx]);
		exec->here_doc_array[idx] = NULL;
	}
	exec->here_doc_array[idx] = ft_calloc(2, sizeof(int));
	if (!exec->here_doc_array[idx])
		return (1);
	if (pipe(exec->here_doc_array[idx]) == -1)
	{
		ft_putendl_fd("MINISHELL: here_doc pipe failure", 2);
		return (2);
	}
	printf("proc[%d]: here_doc; write_end: %d; read_end: %d\n", idx, exec->here_doc_array[idx][T_PIPE_WRITE], exec->here_doc_array[idx][T_PIPE_READ]);
	return (0);
}
