/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 17:02:58 by sharsune          #+#    #+#             */
/*   Updated: 2023/05/27 12:54:51 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	turnoff_echo(struct termios *termios);
void	turnon_echo(struct termios *termios);
void	signal_handler(int signum);
void	ctrl_d_handler(void);
int		get_signals(t_data *data);

/*----------------------------------------------------------------------------*/

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
	// change this later (minishell_exit); also exit code is 0, not 1
	write(1, "exit\n", 5);
	exit(1);
}

int	get_signals(t_data *data)
{
	if (signal(SIGINT, signal_handler) == SIG_ERR || \
	signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (minishell_sig_hand_err_msg(data));
	return (0);
}
