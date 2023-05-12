/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:01:09 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/12 14:01:32 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/executor.h"
#include "../../include/colors.h"

int			main(int argc, char **argv, char **envp);
static char	**minishell_env_setup(char **envp);
static void	minishell_data_set_init_vals(t_data *data);
static int	minishell_sig_hand_err_msg(t_data *data);

/*----------------------------------------------------------------------------*/

int	main(int argc, char **argv, char **envp)
{
	t_data			data;
	struct termios	termios;
	char			*read_line;

	(void)argc;
	(void)argv;
	tcgetattr(STDIN_FILENO, &termios);
	data.envs = minishell_env_setup(envp);
	if (signal(SIGINT, signal_handler) == SIG_ERR || \
	signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (minishell_sig_hand_err_msg(&data));
	minishell_data_set_init_vals(&data);
	while (1)
	{
		turnoff_echo(&termios);
		read_line = readline("\033[0;32mprototype_minishell> \033[0;37m");
		if (read_line == NULL)
			ctrl_d_handler();
		turnon_echo(&termios);
		if (real_minishell_parser(read_line, &data) != 0)
		{
			read_line_clean_up(&data);
			tokens_clean_up(&data);
			continue ;
		}
		read_line_clean_up(&data);
		data.latest_exit_status = real_executor_pre_setup(&data);
		minishell_loop_clean_up(&data);
	}
	return (0);
}

static char	**minishell_env_setup(char **envp)
{
	char	**minishell_env;
	int		shlvl_int;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	minishell_env = malloc((i + 1) * sizeof(char *));
	i = -1;
	while (envp[++i])
	{
		if (ft_strnstr(envp[i], "SHLVL", 5))
		{
			shlvl_int = ft_atoi(envp[i] + 6);
			shlvl_int++;
			minishell_env[i] = ft_strjoin("SHLVL=", ft_itoa(shlvl_int));
		}
		else
		minishell_env[i] = ft_strdup(envp[i]);
	}
	minishell_env[i] = NULL;
	return (minishell_env);
}

static void	minishell_data_set_init_vals(t_data *data)
{
	data->parser.rl_parts_lst = NULL;
	data->parser.token_amount = 0;
	data->parser.token_lst = NULL;
	data->executor.fds_array = NULL;
	data->executor.jobs_amount = 0;
	data->executor.jobs_array = NULL;
	data->executor.token_amount = 0;
	data->executor.token_lst = NULL;
}

static int	minishell_sig_hand_err_msg(t_data *data)
{
	ft_putendl_fd("MINISHELL: Error installing signal handler", 2);
	str_array_free_everything(data->envs);
	return (1);
}
