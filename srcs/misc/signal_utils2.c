/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:19:36 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/25 15:20:10 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	here_doc_signal(int signum)
{
	g_in_here_doc = 0;
	(void) signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}
