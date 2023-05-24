/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 18:16:20 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/23 18:20:42 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/parser.h"
#include "../../include/tokenizer.h"
#include "../../include/executor.h"

void	here_doc_send_str_to_pipe(t_data *data, int process_idx, char *str)
{
	str = here_doc_process_line(str, data);
	write(data->executor.here_doc_array[process_idx][T_PIPE_WRITE],
		str, ft_strlen(str));
	write(data->executor.here_doc_array[process_idx][T_PIPE_WRITE],
		"\n", 1);
	free(str);
}
