/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:58:45 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/21 15:02:57 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"

t_token		*process_get_cmd_token(t_process *proc);
char		*find_cmd_path(char *cmd, char **env);
static char	**get_all_paths(char **envs);

/*----------------------------------------------------------------------------*/

t_token	*process_get_cmd_token(t_process *proc)
{
	int		i;

	i = 0;
	while (proc->tokens_array[i])
	{
		if (proc->tokens_array[i]->type == T_COMMAND)
			return (proc->tokens_array[i]);
		i++;
	}
	return (NULL);
}

char	*find_cmd_path(char *cmd, char **env)
{
	char	**all_paths;
	char	*cmd_path_tmp;
	char	*cmd_path;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	all_paths = get_all_paths(env);
	if (!all_paths)
		return (NULL);
	i = -1;
	while (all_paths[++i])
	{
		cmd_path_tmp = ft_strjoin(all_paths[i], "/");
		cmd_path = ft_strjoin(cmd_path_tmp, cmd);
		free(cmd_path_tmp);
		if (access(cmd_path, F_OK) == 0)
		{
			str_array_free_everything(all_paths);
			return (cmd_path);
		}
		free (cmd_path);
	}
	str_array_free_everything(all_paths);
	return (NULL);
}

static char	**get_all_paths(char **envs)
{
	int	i;

	i = -1;
	while (envs[++i])
	{
		if (ft_strncmp("PATH", envs[i], 4) == 0 && envs[i][4] == '=')
			return (ft_split(envs[i] + 5, ':'));
	}
	return (NULL);
}
