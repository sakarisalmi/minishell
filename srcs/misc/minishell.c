/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:01:09 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/11 13:11:54 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/executor.h"
#include "../../include/colors.h"

int			main(int argc, char **argv, char **envp);
static char	**minishell_env_setup(char **envp);
static int	minishell_sig_hand_err_msg(t_data *data);

/*----------------------------------------------------------------------------*/

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*read_line;

	(void)argc;
	(void)argv;
	data.envs = minishell_env_setup(envp);
	printf("calling env func\n");
	env(&data);
	if (signal(SIGINT, signal_handler) == SIG_ERR || \
	signal(SIGQUIT, signal_handler) == SIG_ERR)
		return (minishell_sig_hand_err_msg(&data));
	while (1)
	{
		read_line = readline("\033[0;32mprototype_minishell> \033[0;37m");
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

static int	minishell_sig_hand_err_msg(t_data *data)
{
	ft_putendl_fd("MINISHELL: Error installing signal handler", 2);
	str_array_free_everything(data->envs);
	return (1);
}
