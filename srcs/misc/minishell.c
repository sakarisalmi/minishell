/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:01:09 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/02 17:09:17 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/colors.h"

int			main(int argc, char **argv, char **envp);
static char	**minishell_env_setup(char **envp);

/*----------------------------------------------------------------------------*/

int	main(int argc, char **argv, char **envp)
{
	t_data			data;
	struct termios	termios;
	char			*read_line;

	(void)argc;
	(void)argv;
	(void)envp;
	tcgetattr(STDIN_FILENO, &termios);
	data.envs = minishell_env_setup(envp);
	printf("calling env func\n");
	env(&data);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (1)
	{
		turnoff_echo(&termios);
		read_line = readline("prototype_minishell> ");
		if (read_line == NULL)
			ctrl_d_handler();
		turnon_echo(&termios);
		minishell_parser(read_line, &data);
		read_line = readline("\033[0;32mprototype_minishell> \033[0;37m");
		test_minishell_parser(read_line, &data);
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
