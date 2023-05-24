/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:33:38 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/22 17:58:58 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	int	check_exit_code(char *str, t_data *data)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			//printf vaihtaa oikeaksi error messageksi.
			printf("minishell: exit: %s: numeric argument required\n", str);
			minishell_loop_clean_up(data);
			str_array_free_everything(data->envs);
			exit(-1);
		}
		i++;
	}
	return (0);
}

int	minishell_exit(char **args, t_data *data)
{
	int	exit_int;

	printf("exit\n");
	if (args[1] && args[1][0] != '0')
	{
		check_exit_code(args[1], data);
		exit_int = ft_atoi(args[1]);
	}
	if (args[2])
	{
		//printf vaihtaa oikeaksi error messageksi.
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (args[1] == NULL)
	{
		minishell_loop_clean_up(data);
		str_array_free_everything(data->envs);
		exit(0);
	}
	else
	{
		minishell_loop_clean_up(data);
		str_array_free_everything(data->envs);
		exit(exit_int);
	}
}
