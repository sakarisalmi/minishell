/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_array_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:49:03 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/10 16:11:52 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"

int			executor_pipe_set_up(t_executor *exec);
static int	set_up_pipes_between_jobs(int *fds, t_job *job_from, t_job *job_to);
void		close_pipe_ends_parent_process(int *fds);
int			**fds_array_create_fds_for_piping(int amount_of_jobs);
void		fds_array_free(int **fds_array, int free_until_idx);

/*----------------------------------------------------------------------------*/

int	executor_pipe_set_up(t_executor *exec)
{
	int	i;

	exec->fds_array = fds_array_create_fds_for_piping(exec->jobs_amount);
	if (!exec->fds_array)
		return (1);
	i = 0;
	while (i < exec->jobs_amount - 1)
	{
		if (set_up_pipes_between_jobs(exec->fds_array[i], exec->jobs_array[i],
				exec->jobs_array[i + 1]) != 0)
			return (2);
		i++;
	}
	return (0);
}

static int	set_up_pipes_between_jobs(int *fds, t_job *job_from, t_job *job_to)
{
	if (pipe(fds) == -1)
	{
		perror("Minishell: Pipe");
		return (1);
	}
	job_from->fd_out = fds[T_PIPE_WRITE];
	job_to->fd_in = fds[T_PIPE_READ];
	return (0);
}

void	close_pipe_ends_parent_process(int *fds)
{
	close(fds[0]);
	close(fds[1]);
}

int	**fds_array_create_fds_for_piping(int amount_of_jobs)
{
	int	**fds_array;
	int	i;

	fds_array = ft_calloc(amount_of_jobs - 1, sizeof(int *));
	if (!fds_array)
		return (NULL);
	i = 0;
	while (i < amount_of_jobs - 1)
	{
		fds_array[i] = ft_calloc(2, sizeof(int));
		if (!fds_array[i])
		{
			fds_array_free(fds_array, i);
			return (NULL);
		}
		i++;
	}
	return (fds_array);
}

void	fds_array_free(int **fds_array, int free_until_idx)
{
	int	i;

	i = 0;
	while (i < free_until_idx)
	{
		free(fds_array[i]);
		i++;
	}
	free(fds_array);
}
