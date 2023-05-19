/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:34:55 by Sharsune          #+#    #+#             */
/*   Updated: 2023/05/19 15:36:10 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/builtin.h"

int			export(char **args, t_data *data);
static void	export_print(t_data *data);
static char	**export_find_match(char *new_str, char **envs);
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
			ft_putstr_fd("MINISHELL: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putendl_fd("\': not a valid identifier", 2);
			result = 1;
		}
		else
			data->envs = export_find_match(args[i], data->envs);
	}
	return (result);
}

static void	export_print(t_data *data)
{
	int	i;

	i = -1;
	while (data->envs[++i])
	{
		printf("declare -x ");
		printf("%s\n", data->envs[i]);
	}
}

static char	**export_find_match(char *new_str, char **envs)
{
	int	i;
	int	j;
	int	found_match;

	found_match = 0;
	j = 0;
	while (new_str[j] && new_str[j] != '=')
		j++;
	i = -1;
	while (envs[++i] && found_match == 0)
	{
		if (ft_strncmp(new_str, envs[i], j) == 0 && (envs[i][j] == '='
			|| envs[i][j] == '\0'))
		{
			found_match = 1;
			envs[i] = export_replace_match(new_str, envs[i]);
		}
	}
	if (found_match == 0)
		envs = str_array_add_str(envs, export_create_new_var(new_str));
	return (envs);
}

static char	*export_replace_match(char *new_str, char *env_str)
{
	int		i;
	char	*new_env_str;

	printf("in export replace match\n");
	i = 0;
	while (new_str[i] && new_str[i] != '=')
		i++;
	if (new_str[i] == '=')
	{
		free(env_str);
		new_env_str = ft_calloc(ft_strlen(new_str) + 3, sizeof(char));
		ft_strncat(new_env_str, new_str, ++i);
		ft_strncat(new_env_str, "\"", 1);
		ft_strncat(new_env_str, new_str + i, ft_strlen(new_str + i));
		ft_strncat(new_env_str, "\"", 1);
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
			if (str[i] == '=')
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
