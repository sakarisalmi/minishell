/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharsune <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:02:58 by sharsune          #+#    #+#             */
/*   Updated: 2023/04/27 17:03:00 by sharsune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	turnoff_echo(struct termios *termios)
{
	termios->c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, termios);
}

void	turnon_echo(struct termios *termios)
{
	termios->c_lflag |= ECHOCTL;
	tcsetattr(0, TCSANOW, termios);
}

void	signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
	}
	if (signum == SIGQUIT)
	{
	}
}

void	ctrl_d_handler(void)
{
	printf("exit\n");
	exit(1);
}