/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_loop_clean_up.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 12:20:19 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/17 14:01:35 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/executor.h"

/*	This function is called after the successfull executor call. */
void	minishell_loop_clean_up(t_data *data)
{
	tokens_clean_up(data);
	executor_clean_up(data, data->executor.process_amount);
}
