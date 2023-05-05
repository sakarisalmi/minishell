/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_array_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:49:03 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/05 15:00:39 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"

int		**fds_array_create_fds_for_piping(int amount_of_jobs);
void	fds_array_free(int **fds_array, int free_until_idx);

/*----------------------------------------------------------------------------*/

// int	executor_pipe_set_up(t_executor *exec)
// {
// 	int	result;

// 	exec->fds_array = fds_array_create_fds_for_piping(exec->jobs_amount);
// 	if (!exec->fds_array)
// 		return (1);
	
// }

// int	set_up_pipes_between_jobs(int *fds, t_job *job_from, t_job *job_to)
// {
// 	pipe(fds);
	
	
// }

// int	**fds_array_create_fds_for_piping(int amount_of_jobs)
// {
// 	int	**fds_array;
// 	int	i;

// 	fds_array = ft_calloc(amount_of_jobs - 1, sizeof(int *));
// 	if (!fds_array)
// 		return (NULL);
// 	i = 0;
// 	while (i < amount_of_jobs - 1)
// 	{
// 		fds_array[i] = ft_calloc(2, sizeof(int));
// 		if (!fds_array[i])
// 		{
// 			fds_array_free(fds_array, i);
// 			return (NULL);
// 		}
// 		i++;
// 	}
// 	return (fds_array);
// }

// void	fds_array_free(int **fds_array, int free_until_idx)
// {
// 	int	i;

// 	i = 0;
// 	while (i < free_until_idx)
// 	{
// 		free(fds_array[i][0]);
// 		free(fds_array[i][1]);
// 		i++;
// 	}
// 	free(fds_array);
// }
