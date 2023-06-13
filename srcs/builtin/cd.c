/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:40:47 by Sharsune          #+#    #+#             */
/*   Updated: 2023/06/07 17:00:27 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/builtin.h"

int			cd(char **args, t_data *data);
static char	**cd_get_export(char *env_var);
static char	*cd_get_home_dir(char **envs, char **export_pwd);
static int	cd_chdir_failure(char **export_pwd, char *arg);
static int	cd_change_dir(char *dir);

/*----------------------------------------------------------------------------*/

int	cd(char **args, t_data *data)
{
	t_cd_func	f;

	f.export_pwd = cd_get_export("OLDPWD=");
	if (!args[1] || !ft_strncmp(args[1], "$HOME", 6))
	{
		f.dir = cd_get_home_dir(data->envs, f.export_pwd);
		if (!f.dir)
			return (1);
	}
	else if (args[1])
		f.dir = args[1];
	f.result = cd_change_dir(f.dir);
	if (f.result == -1)
		return (cd_chdir_failure(f.export_pwd, args[1]));
	else
	{
		export(f.export_pwd, data);
		str_array_free_everything(f.export_pwd);
		f.export_pwd = cd_get_export("PWD=");
		export(f.export_pwd, data);
		str_array_free_everything(f.export_pwd);
	}
	return (f.result);
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

static char	*cd_get_home_dir(char **envs, char **export_pwd)
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
	str_array_free_everything(export_pwd);
	return (NULL);
}

static int	cd_chdir_failure(char **export_pwd, char *arg)
{
	ft_putstr_fd("MINISHELL: cd: ", 2);
	perror(arg);
	str_array_free_everything(export_pwd);
	return (1);
}

static int	cd_change_dir(char *dir)
{
	int	result;

	if (dir[0] == '\0')
		result = 0;
	else
		result = chdir(dir);
	return (result);
}
