/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:01:09 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/05 15:36:21 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/executor.h"
#include "../../include/colors.h"

int			main(int argc, char **argv, char **envp);
static void	minishell_set_up(t_data *data, char **envp, int argc, char **argv);
static void	minishell_data_set_init_vals(t_data *data);
int			minishell_sig_hand_err_msg(t_data *data);

/*----------------------------------------------------------------------------*/

int	main(int argc, char **argv, char **envp)
{
	t_data			data;
	struct termios	termios;
	char			*read_line;

	tcgetattr(STDIN_FILENO, &termios);
	minishell_set_up(&data, envp, argc, argv);
	while (1)
	{
		get_signals(&data);
		turnoff_echo(&termios);
		read_line = readline("\033[0;32mMINISHELL> \033[0;37m");
		turnon_echo(&termios);
		if (read_line == NULL)
			ctrl_d_handler();
		if (minishell_parser(read_line, &data) != 0)
		{
			read_line_parts_clean_up(&data);
			tokens_clean_up(&data);
			continue ;
		}
		read_line_parts_clean_up(&data);
		data.latest_exit_status = executor_pre_setup(&data);
		minishell_loop_clean_up(&data);
	}
	return (0);
}

static void	minishell_set_up(t_data *data, char **envp, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	data->envs = minishell_env_setup(envp);
	minishell_data_set_init_vals(data);
}

static void	minishell_data_set_init_vals(t_data *data)
{
	data->parser.rl_parts_lst = NULL;
	data->parser.token_amount = 0;
	data->parser.token_lst = NULL;
	data->executor.fds_array = NULL;
	data->executor.here_doc_array = NULL;
	data->executor.process_amount = 0;
	data->executor.process_array = NULL;
	data->executor.token_amount = 0;
	data->executor.token_lst = NULL;
	g_in_here_doc = 0;
}

int	minishell_sig_hand_err_msg(t_data *data)
{
	ft_putendl_fd("MINISHELL: Error installing signal handler", 2);
	str_array_free_everything(data->envs);
	return (1);
}
