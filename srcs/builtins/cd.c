/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sharsune <sharsune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 14:40:47 by Sharsune          #+#    #+#             */
/*   Updated: 2023/05/11 14:40:49 by Sharsune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	cd(char **args)
{
	char	*dir;

	if (!args)
		dir = getenv("HOME");
	else if (args)
		dir = args[0];
	chdir(dir);
	return (0);
}
