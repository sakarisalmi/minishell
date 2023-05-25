/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:33:38 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/25 15:01:09 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int			minishell_exit(char **args, t_data *data);
static int	minishell_exit_check_first_arg(char *arg);
static int	minishell_check_exit_code(char *str);
static void	minishell_exit_print_err_msg(char *arg);

/*----------------------------------------------------------------------------*/

int	minishell_exit(char **args, t_data *data)
{
	int	exit_int;
	int	i;

	printf("exit\n");
	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		return (1);
	}
	if (!args[1] || minishell_exit_check_first_arg(args[1]))
		exit_int = 0;
	else
	{
		if (minishell_check_exit_code(args[1]))
			exit_int = -1;
		else
			exit_int = ft_atoi(args[1]);
	}
	minishell_loop_clean_up(data);
	str_array_free_everything(data->envs);
	exit(exit_int);
}

static int	minishell_exit_check_first_arg(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
	{
		if (i == 0)
		{
			if (arg[i] != '0' || (arg[i] != '-'
					&& arg[i] != '+' && arg[i + 1] != '0'))
				return (0);
		}
		else
			if (arg[i] != '0')
				return (0);
	}
	return (1);
}

static int	minishell_check_exit_code(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
	{
		minishell_exit_print_err_msg(str);
		return (1);
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			minishell_exit_print_err_msg(str);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	minishell_exit_print_err_msg(char *arg)
{
	char	*error_msg;

	error_msg = ft_calloc(45 + ft_strlen(arg), sizeof(char));
	if (!error_msg)
	{
		ft_putendl_fd("MINISHELL: exit: malloc failure", 2);
		return ;
	}
	ft_strncat(error_msg, "MINISHELL: exit: ", ft_strlen("MINISHELL: exit: "));
	ft_strncat(error_msg, arg, ft_strlen(arg));
	ft_strncat(error_msg, ": numeric argument required",
		ft_strlen(": numeric argument required"));
	ft_putendl_fd(error_msg, 2);
	free(error_msg);
}
