/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:31:44 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/04 15:10:32 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(void)
{
	char	cwd[4096];

	if (getcwd(cwd, 4096) == NULL)
	{
		free(cwd);
		perror("getcwd() error");
		return (1);
	}
	else
	{
		ft_printf("%s\n", cwd);
		return (0);
	}
}
