/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:34:55 by Sharsune          #+#    #+#             */
/*   Updated: 2023/05/27 14:01:25 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int			export(char **args, t_data *data);
static void	export_print(t_data *data);
static char	**export_find_match(char *new_str, char **envs, t_data *data);
static char	*export_replace_match(char *new_str, char *env_str);
static int	export_check_if_invalid(char *str);

/*----------------------------------------------------------------------------*/

int	export(char **args, t_data *data)
{
	int	i;
	int	result;

	result = 0;
	if (!args[1])
	{
		export_print(data);
		return (0);
	}
	i = 0;
	while (args[++i])
	{
		if (export_check_if_invalid(args[i]))
		{
			export_and_unset_error_msg("export", args[i]);
			result = 1;
		}
		else
			data->envs = export_find_match(args[i], data->envs, data);
	}
	return (result);
}

static void	export_print(t_data *data)
{
	char	*str_print;
	int		i;
	int		j;

	i = -1;
	while (data->envs[++i])
	{
		printf("declare -x ");
		j = 0;
		while (data->envs[i][j] != '=' && data->envs[i][j] != '\0')
			j++;
		if (!data->envs[i][j])
			printf("%s\n", data->envs[i]);
		else
		{
			str_print = ft_calloc(ft_strlen(data->envs[i]) + 3, sizeof(char));
			ft_strncat(str_print, data->envs[i], ++j);
			ft_strncat(str_print, "\"", 1);
			ft_strncat(str_print, data->envs[i] + j,
				ft_strlen(data->envs[i] + j));
			ft_strncat(str_print, "\"", 1);
			printf("%s\n", str_print);
			free(str_print);
		}
	}
}

static char	**export_find_match(char *new_str, char **envs, t_data *data)
{
	int	i;
	int	j;
	int	found_match;

	found_match = 0;
	j = 0;
	while (new_str[j] && new_str[j] != '=' && new_str[j] != '+')
		j++;
	i = -1;
	while (envs[++i] && found_match == 0)
	{
		if (ft_strncmp(new_str, envs[i], j) == 0 && (envs[i][j] == '='
			|| envs[i][j] == '+' || envs[i][j] == '\0'))
		{
			found_match = 1;
			envs[i] = export_replace_match(new_str, envs[i]);
		}
	}
	if (found_match == 0)
		envs = export_add_new_var(new_str, envs, data);
	return (envs);
}

static char	*export_replace_match(char *new_str, char *env_str)
{
	int		i;
	char	*new_env_str;

	i = 0;
	while (new_str[i] && new_str[i] != '=' && new_str[i] != '+')
		i++;
	if (new_str[i] == '+')
	{
		new_env_str = ft_strjoin(env_str, new_str + i + 2);
		free(env_str);
		return (new_env_str);
	}
	else if (new_str[i] == '=')
	{
		free(env_str);
		new_env_str = ft_calloc(ft_strlen(new_str) + 1, sizeof(char));
		ft_strncat(new_env_str, new_str, ft_strlen(new_str));
		return (new_env_str);
	}
	return (env_str);
}

static int	export_check_if_invalid(char *str)
{
	int	i;
	int	equals_sign;

	equals_sign = 0;
	i = -1;
	while (str[++i] && equals_sign == 0)
	{
		if (i == 0 && !ft_isalpha(str[i]) && str[i] != '_')
			return (1);
		else
		{
			if (str[i] == '=' || (str[i] == '+' && str[i + 1] == '='))
				equals_sign = 1;
			else
				if (!ft_isalnum(str[i]) && str[i] != '_')
					return (1);
		}
	}
	if (i == 0)
		return (1);
	return (0);
}
