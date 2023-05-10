/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_error_msg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:34:35 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/10 11:43:58 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"
#include "../../include/tokenizer.h"

/*	This function handle's printing out the error message that happen in
	the executor; done to save precious space in other functions.
	The error code tells the function what error message to print and
	what to return.
	Error codes:
	1. fork failure
	2. executor_pipe_set_up failure
	3. execve failure
	4. command not found
	*/
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
		return (1);
	}
	if (error_code == 3)
	{
		perror("MINISHELL: execve");
		exit(1);
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
