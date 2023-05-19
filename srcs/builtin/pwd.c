/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:31:44 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/19 15:53:57 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(void)
{
	char	*cwd;

	cwd = ft_calloc(4096, sizeof(char));
	if (!cwd)
	{
		ft_putendl_fd("MINISHELL: pwd: allocation error", 2);
		return (1);
	}
	if (getcwd(cwd, 4096) == NULL)
	{
		perror("getcwd() error");
		free(cwd);
		return (1);
	}
	else
	{
		ft_printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
}
