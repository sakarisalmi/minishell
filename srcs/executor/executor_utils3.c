/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:45:44 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/08 18:48:30 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"

void	executor_close_proc_fds(t_process *proc)
{
	if (proc->fd_in != STDIN_FILENO)
		close(proc->fd_in);
	if (proc->fd_out != STDOUT_FILENO)
		close(proc->fd_out);
}
