/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_array_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:32:58 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/15 15:28:07 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"

void		close_all_pipe_fds(t_executor *exec);
int			**executor_set_up_here_doc_array(t_executor *exec);
static int	**executor_create_here_doc_array(t_executor *exec);
static int	executor_set_up_here_doc_pipes(t_executor *exec);

/*----------------------------------------------------------------------------*/

void	close_all_pipe_fds(t_executor *exec)
{
	int	i;

	i = -1;
	if (exec->fds_array)
		while (++i < exec->jobs_amount - 1)
		{
			close(exec->fds_array[i][0]);
			close(exec->fds_array[i][1]);
		}
	i = -1;
	while (++i < exec->jobs_amount)
	{
		close(exec->here_doc_array[i][0]);
		close(exec->here_doc_array[i][1]);
	}
}

int	**executor_set_up_here_doc_array(t_executor *exec)
{
	int	**here_doc_array;
	int	i;

	here_doc_array = executor_create_here_doc_array(exec);
	if (!here_doc_array)
		return (NULL);
	i = -1;
	if (executor_set_up_here_doc_pipes(exec) != 0)
	{
		fds_array_free(here_doc_array, exec->jobs_amount);
		return (NULL);
	}
	return (here_doc_array);
}

static int	**executor_create_here_doc_array(t_executor *exec)
{
	int	**here_doc_array;
	int	i;

	here_doc_array = ft_calloc(exec->jobs_amount, sizeof(int *));
	if (!here_doc_array)
	{
		ft_putendl_fd("MINISHELL: error: here_doc_array alloc failure", 2);
		return (NULL);
	}
	i = -1;
	while (++i < exec->jobs_amount)
	{
		here_doc_array[i] = ft_calloc(2, sizeof(int));
		if (!here_doc_array[i])
		{
			ft_putendl_fd("MINISHELL: error: here_doc_array allocation \
				failure", 2);
			fds_array_free(here_doc_array, i);
			return (NULL);
		}
	}
	return (here_doc_array);
}

static int	executor_set_up_here_doc_pipes(t_executor *exec)
{
	int	i;

	i = -1;
	while (i < exec->jobs_amount)
	{
		if (pipe(exec->here_doc_array[i]) == -1)
		{
			perror("MINISHELL: here_doc");
			return (1);
		}
	}
	return (0);
}
