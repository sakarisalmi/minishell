/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:43:03 by Sharsune          #+#    #+#             */
/*   Updated: 2023/05/19 17:53:05 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int			unset(char **args, t_data *data);
static int	unset_check_if_invalid(char *str);
static char	**unset_find_match_and_remove(char *str, char **envs);
void		export_and_unset_error_msg(char *func_name, char *arg);

/*----------------------------------------------------------------------------*/

int	unset(char **args, t_data *data)
{
	int	result;
	int	i;

	result = 0;
	if (!args[1])
		return (result);
	i = 0;
	while (args[++i])
	{
		if (unset_check_if_invalid(args[i]))
		{
			export_and_unset_error_msg("unset", args[i]);
			result = 1;
		}
		else
			data->envs = unset_find_match_and_remove(args[i], data->envs);
	}
	return (result);
}

static int	unset_check_if_invalid(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0)
		{
			if (!ft_isalpha(str[i]) && str[i] != '_')
				return (1);
		}
		else
			if (!ft_isalnum(str[i]) && str[i] != '_')
				return (1);
	}
	return (0);
}

static char	**unset_find_match_and_remove(char *str, char **envs)
{
	int	i;

	i = -1;
	while (envs[++i])
	{
		if (ft_strncmp(str, envs[i], ft_strlen(str)) == 0
			&& (envs[i][ft_strlen(str)] == '='
			|| envs[i][ft_strlen(str)] == '\0'))
			return (str_array_remove_str_by_index(envs, i));
	}
	return (envs);
}

void	export_and_unset_error_msg(char *func_name, char *arg)
{
	char	*print_str;

	print_str = ft_calloc(ft_strlen(func_name) + ft_strlen(arg)+ 39,
			sizeof(char));
	if (!print_str)
	{
		ft_putendl_fd("MINISHELL: export_and_unset_error_msg:\
		allocation failure", 2);
		return ;
	}
	ft_strncat(print_str, "MINISHELL: ", ft_strlen("MINISHELL: "));
	ft_strncat(print_str, func_name, ft_strlen(func_name));
	ft_strncat(print_str, ": `", ft_strlen(": `"));
	ft_strncat(print_str, arg, ft_strlen(arg));
	ft_strncat(print_str, "': not a valid identifier",
		ft_strlen("': not a valid identifier"));
	ft_putendl_fd(print_str, 2);
	free(print_str);
}
