/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_cmd_utils1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 15:58:45 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/17 14:01:23 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"

t_token	*process_get_cmd_token(t_process *proc);
char	*find_cmd_path(char *cmd, char **env);

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

	all_paths = NULL;
	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	i = -1;
	while (env[++i])
		if (ft_strncmp("PATH", env[i], 4) == 0)
			all_paths = ft_split(env[i] + 5, ':');
	if (!all_paths)
		return (NULL);
	i = -1;
	while (all_paths[++i])
	{
		cmd_path_tmp = ft_strjoin(all_paths[i], "/");
		cmd_path = ft_strjoin(cmd_path_tmp, cmd);
		free(cmd_path_tmp);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free (cmd_path);
	}
	return (NULL);
}
