/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 13:27:37 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/19 17:52:34 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "minishell.h"

// check_for_builtin.c
int		check_for_builtin(t_token **tokens_array);

// cd.c
int		cd(char **args, t_data *data);

// pwd.c
int		pwd(void);

// env.c
int		env(t_data *data);

// echo.c
int		echo(char **args);

// unset.c
int		unset(char **args, t_data *data);
void	export_and_unset_error_msg(char *func_name, char *arg);

// export.c
int		export(char **args, t_data *data);

// exit.c
int		minishell_exit(char **args, t_data *data);

#endif