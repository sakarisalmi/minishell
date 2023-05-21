/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 16:33:38 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/21 14:20:52 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	minishell_exit(t_data *data)
{
	printf("exit\n");
	minishell_loop_clean_up(data);
	str_array_free_everything(data->envs);
	exit(0);
}
