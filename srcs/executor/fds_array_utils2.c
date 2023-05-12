/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_array_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 15:32:58 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/10 15:43:47 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"

void	child_process_close_all_fds(t_executor *exec)
{
	int	i;

	i = -1;
	while (++i < exec->jobs_amount - 1)
	{
		close(exec->fds_array[i][0]);
		close(exec->fds_array[i][1]);
	}
}
