/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:40:47 by Sharsune          #+#    #+#             */
/*   Updated: 2023/05/25 13:13:24 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/builtin.h"

int			cd(char **args, t_data *data);
static char	**cd_get_export(char *env_var);
static char	*cd_get_home_dir(char **envs);
static int	cd_chdir_failure(char **export_pwd);

/*----------------------------------------------------------------------------*/

int	cd(char **args, t_data *data)
{
	int		result;
	char	**export_pwd;
	char	*dir;

	export_pwd = cd_get_export("OLDPWD=");
	if (!args[1] || !ft_strncmp(args[1], "$HOME", 6))
	{
		dir = cd_get_home_dir(data->envs);
		if (!dir)
			return (1);
	}
	else if (args[1])
		dir = args[1];
	result = chdir(dir);
	if (result == -1)
		return (cd_chdir_failure(export_pwd));
	else
	{
		export(export_pwd, data);
		str_array_free_everything(export_pwd);
		export_pwd = cd_get_export("PWD=");
		export(export_pwd, data);
		str_array_free_everything(export_pwd);
	}
	return (result);
}

static char	**cd_get_export(char *env_var)
{
	char	*cwd;
	char	**export_cwd;

	export_cwd = ft_calloc(3, sizeof(char *));
	if (!export_cwd)
		return (NULL);
	cwd = ft_calloc(4096, sizeof(char));
	if (!cwd)
	{
		free(export_cwd);
		return (NULL);
	}
	getcwd(cwd, 4096);
	export_cwd[0] = ft_strdup("export");
	export_cwd[1] = ft_strjoin(env_var, cwd);
	export_cwd[2] = NULL;
	free(cwd);
	return (export_cwd);
}

static char	*cd_get_home_dir(char **envs)
{
	int	i;

	if (!envs)
		return (NULL);
	i = -1;
	while (envs[++i])
	{
		if (ft_strncmp("HOME", envs[i], ft_strlen("HOME")) == 0
			&& envs[i][ft_strlen("HOME")] == '=')
			return (envs[i] + 5);
	}
	ft_putendl_fd("MINISHELL: cd: HOME not set", 2);
	return (NULL);
}

static int	cd_chdir_failure(char **export_pwd)
{
	perror("MINISHELL: cd");
	str_array_free_everything(export_pwd);
	return (1);
}
