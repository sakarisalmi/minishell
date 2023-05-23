/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:02:58 by sharsune          #+#    #+#             */
/*   Updated: 2023/05/23 13:39:42 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	turnoff_echo(struct termios *termios);
void	turnon_echo(struct termios *termios);
void	signal_handler(int signum);
void	ctrl_d_handler(void);
void	here_doc_signal(int signum);

/*----------------------------------------------------------------------------*/

// the global variable used for signals
extern int	g_in_here_doc;

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
}

void	ctrl_d_handler(void)
{
	write(1, "exit\n", 5);
	exit(1);
}

void	here_doc_signal(int signum)
{
	g_in_here_doc = 0;
	(void) signum;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}
