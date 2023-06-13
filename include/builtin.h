/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:27:37 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/07 16:52:04 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

typedef struct s_cd_func
{
	int		result;
	char	**export_pwd;
	char	*dir;
}	t_cd_func;

/*----------------------------------------------------------------------------*/

# include "minishell.h"

// check_for_builtin.c
int		check_for_builtin(t_token **tokens_array);

// cd.c
int		cd(char **args, t_data *data);

// pwd.c
int		pwd(void);

// env.c
int		env(char **args, t_data *data);

// echo.c
int		echo(char **args);

// unset.c
int		unset(char **args, t_data *data);
void	export_and_unset_error_msg(char *func_name, char *arg);

// export.c
int		export(char **args, t_data *data);

// export_utils1.c
char	**export_add_new_var(char *new_str, char **envs, t_data *data);

// exit.c
int		minishell_exit(char **args, t_data *data);

#endif