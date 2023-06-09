/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_setup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:34:58 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/12 15:41:07 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char		**minishell_env_setup(char **envp);
static char	*minishell_env_setup_strdup(char *str, int idx,
				char **minishell_env);
static char	*minishell_env_setup_copy_shlvl(char *str, int idx,
				char **minishell_env);
static char	**minishell_env_check_shlvl(char **envs);

/*----------------------------------------------------------------------------*/

char	**minishell_env_setup(char **envp)
{
	t_envs_set_up_func	f;

	f.i = 0;
	while (envp[f.i])
		f.i++;
	f.minishell_env = malloc((f.i + 1) * sizeof(char *));
	if (!f.minishell_env)
		exit(-1);
	f.i = -1;
	while (envp[++f.i])
	{
		if (ft_strnstr(envp[f.i], "SHLVL=", 6))
			f.minishell_env[f.i] = minishell_env_setup_copy_shlvl(envp[f.i],
					f.i, f.minishell_env);
		else
			f.minishell_env[f.i] = minishell_env_setup_strdup(envp[f.i],
					f.i, f.minishell_env);
	}
	f.minishell_env[f.i] = NULL;
	f.minishell_env = minishell_env_check_shlvl(f.minishell_env);
	return (f.minishell_env);
}

static char	*minishell_env_setup_strdup(char *str, int idx,
				char **minishell_env)
{
	int		i;
	char	*copied_str;

	copied_str = ft_strdup(str);
	if (!copied_str)
	{
		ft_putendl_fd("MINISHELL: env_setup malloc failure; FATAL ERROR", 2);
		i = -1;
		while (++i < idx)
			free(minishell_env[i]);
		free(minishell_env);
		exit (-1);
	}
	return (copied_str);
}

static char	*minishell_env_setup_copy_shlvl(char *str, int idx,
				char **minishell_env)
{
	t_envs_set_up_shlvl_func	f;

	f.i = -1;
	f.shlvl_int = ft_atoi(str + 6);
	f.shlvl_int++;
	f.shlvl_str = ft_itoa(f.shlvl_int);
	if (!f.shlvl_str)
	{
		ft_putendl_fd("MINISHELL: env_setup malloc failure; FATAL ERROR", 2);
		while (++f.i < idx)
			free(minishell_env[f.i]);
		free(minishell_env);
		exit (-1);
	}
	f.str_to_return = ft_strjoin("SHLVL=", f.shlvl_str);
	free(f.shlvl_str);
	if (!f.str_to_return)
	{
		ft_putendl_fd("MINISHELL: env_setup malloc failure; FATAL ERROR", 2);
		while (++f.i < idx)
			free(minishell_env[f.i]);
		free(minishell_env);
		exit (-1);
	}
	return (f.str_to_return);
}

/*	this function checks if there is no shlvl in the copied environment values.
	If there is a shlvl, do nothing. Otherwise create shlvl (set it to 1). */
static char	**minishell_env_check_shlvl(char **envs)
{
	char	*shlvl_str;
	int		i;

	i = -1;
	while (envs[++i])
	{
		if (ft_strnstr(envs[i], "SHLVL=", 6))
			return (envs);
	}
	shlvl_str = ft_strdup("SHLVL=1");
	if (!shlvl_str)
	{
		ft_putendl_fd("MINISHELL: failed to malloc shlvl", 2);
		return (envs);
	}
	envs = str_array_add_str(envs, shlvl_str);
	return (envs);
}
