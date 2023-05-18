/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:40:47 by Sharsune          #+#    #+#             */
/*   Updated: 2023/05/18 14:22:11 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/builtin.h"

int			cd(char **args, t_data *data);
static char	**cd_get_export(char *env_var);

/*----------------------------------------------------------------------------*/

int	cd(char **args, t_data *data)
{
	int		result;
	char	**export_pwd;
	char	*dir;

	export_pwd = cd_get_export("OLD_PWD=");
	if (!args[1])
		dir = getenv("HOME");
	else if (args[1])
		dir = args[1];
	result = chdir(dir);
	if (result == -1)
	{
		perror("MINISHELL: cd");
		free(export_pwd);
		return (1);
	}
	else
	{
		export(export_pwd, data);
		free(export_pwd);
		export_pwd = cd_get_export("PWD=");
		export(export_pwd, data);
		free(export_pwd);
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
		return (NULL);
	getcwd(cwd, 4096);
	export_cwd[0] = ft_strdup("export");
	export_cwd[1] = ft_strjoin(env_var, cwd);
	export_cwd[2] = NULL;
	free(cwd);
	return (export_cwd);
}
