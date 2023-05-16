/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_clean_up.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 16:52:21 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/15 14:35:28 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/executor.h"

void		executor_clean_up(t_data *data, int jobs_amount);
static void	executor_clean_up_continued(t_data *data);

/*----------------------------------------------------------------------------*/

/*	This function frees everything allocated for the executor and set it so
	that there is a "clean" slate for the next time the executor is needed.	*/
void	executor_clean_up(t_data *data, int jobs_amount)
{
	t_executor	*ex;
	int			i;

	ex = &data->executor;
	if (ex->fds_array)
	{
		fds_array_free(ex->fds_array, ex->jobs_amount - 1);
		ex->fds_array = NULL;
	}
	if (ex->here_doc_array)
	{
		fds_array_free(ex->here_doc_array, ex->jobs_amount);
		ex->here_doc_array = NULL;
	}
	i = -1;
	while (++i < jobs_amount)
	{
		free(ex->jobs_array[i]->tokens_array);
		if (ex->jobs_array[i]->cmd_path)
			free(ex->jobs_array[i]->cmd_path);
		free(ex->jobs_array[i]);
	}
	executor_clean_up_continued(data);
}

static void	executor_clean_up_continued(t_data *data)
{
	t_executor	*ex;

	ex = &data->executor;
	free(ex->jobs_array);
	ex->jobs_array = NULL;
	ex->token_amount = 0;
	ex->jobs_amount = 0;
	ex->token_lst = NULL;
}
