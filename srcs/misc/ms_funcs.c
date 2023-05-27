/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_funcs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 17:12:59 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/27 12:47:37 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"

void	*ms_calloc(size_t count, size_t size, t_data *data);
void	*ms_realloc(void *ptr, size_t size, t_data *data);
void	minishell_fatal_error_exit(t_data *data);

/*----------------------------------------------------------------------------*/

void	*ms_calloc(size_t count, size_t size, t_data *data)
{
	void	*new_ptr;

	new_ptr = ft_calloc(count, size);
	if (!new_ptr)
		minishell_fatal_error_exit(data);
	return (new_ptr);
}

void	*ms_realloc(void *ptr, size_t size, t_data *data)
{
	void		*new_ptr;

	new_ptr = ft_realloc(ptr, size);
	if (!new_ptr)
		minishell_fatal_error_exit(data);
	return (new_ptr);
}

void	minishell_fatal_error_exit(t_data *data)
{
	ft_putendl_fd("MINISHELL: malloc failure; FATAL ERROR", 2);
	read_line_parts_clean_up(data);
	minishell_loop_clean_up(data);
	str_array_free_everything(data->envs);
	exit (-1);
}
