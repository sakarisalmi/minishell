/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:34:35 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/11 18:15:57 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/tokenizer.h"

int	executor_error_msg(char *s, int error_code);
int	executor_get_latest_exit_status(int lexit);

/*----------------------------------------------------------------------------*/

/*	This function handle's printing out the error message that happen in
	the executor; done to save precious space in other functions.
	The error code tells the function what error message to print and
	what to return.
	Error codes:
	1. fork failure
	2. executor_pipe_set_up failure
	3. execve failure
	4. command not found	*/
int	executor_error_msg(char *s, int error_code)
{
	if (error_code == 1)
	{
		perror("MINISHELL: fork");
		return (-1);
	}
	if (error_code == 2)
	{
		ft_putendl_fd("MINISHELL: executor_pipe_set_up failure", 2);
		return (-1);
	}
	if (error_code == 3)
	{
		perror("MINISHELL: execve");
		exit(-1);
	}
	if (error_code == 4)
	{
		ft_putstr_fd("MINISHELL: ", 2);
		ft_putstr_fd(s, 2);
		ft_putendl_fd(": command not found", 2);
		exit(127);
	}
	return (0);
}

/*	This function returns the correct exit status of the latest process for
	the executor to return to the minishell so
	that the data's latest_exit_status can be set.*/
int	executor_get_latest_exit_status(int lexit)
{
	if (WIFEXITED(lexit))
		return (WIFEXITED(lexit));
	if (WIFSIGNALED(lexit))
		return (WTERMSIG(lexit));
	return (0);
}
