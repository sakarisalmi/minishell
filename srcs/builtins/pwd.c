/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:31:44 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/18 13:35:08 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
	{
		perror("getcwd() error");
		return (1);
	}
	else
	{
		ft_printf("%s\n", cwd);
		free(cwd);
		return (0);
	}
}
