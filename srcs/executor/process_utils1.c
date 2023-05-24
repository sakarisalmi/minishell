/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:38:36 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/23 14:10:54 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"

t_process			**create_processes_from_tokens(t_token *token_lst);
static t_process	**executor_process_array_add_new_job(t_process **proc_array,
						t_process *new_process);
static t_process	*process_init_new_process(void);
static t_token		**process_tokens_array_add_new_token(t_token **tokens_array,
						t_token *new_token);
void				process_free_process(t_process *job);

/*----------------------------------------------------------------------------*/

t_process	**create_processes_from_tokens(t_token *token_lst)
{
	t_token		*tmp_token;
	t_process	**proc_array;
	int			i;

	proc_array = ft_calloc(1, sizeof(t_process *));
	if (!proc_array)
		return (NULL);
	proc_array[0] = NULL;
	tmp_token = token_lst;
	i = 0;
	while (tmp_token)
	{
		if (proc_array[i] == NULL)
		{
			proc_array = executor_process_array_add_new_job(proc_array,
					process_init_new_process());
		}
		if (tmp_token->type == T_PIPE)
			i++;
		else
			proc_array[i]->tokens_array = process_tokens_array_add_new_token(
					proc_array[i]->tokens_array, tmp_token);
		tmp_token = tmp_token->next;
	}
	return (proc_array);
}

static t_process	**executor_process_array_add_new_job(t_process **proc_array,
	t_process *new_process)
{
	t_process	**new_process_array;
	int			size;
	int			i;

	size = 0;
	while (proc_array[size])
		size++;
	new_process_array = ft_calloc(size + 2, sizeof(t_process *));
	if (!new_process_array)
		return (NULL);
	i = -1;
	while (++i < size)
		new_process_array[i] = proc_array[i];
	free(proc_array);
	new_process_array[i] = new_process;
	new_process_array[i + 1] = NULL;
	return (new_process_array);
}

static t_process	*process_init_new_process(void)
{
	t_process	*new_process;

	new_process = malloc(sizeof(t_process));
	if (!new_process)
		return (NULL);
	new_process->tokens_array = malloc(sizeof(t_token *));
	if (!new_process->tokens_array)
		return (NULL);
	new_process->tokens_array[0] = NULL;
	new_process->fd_in = STDIN_FILENO;
	new_process->fd_out = STDOUT_FILENO;
	new_process->cmd_path = NULL;
	return (new_process);
}

static t_token	**process_tokens_array_add_new_token(t_token **tokens_array,
	t_token *new_token)
{
	t_token	**new_tokens_array;
	int		size;
	int		i;

	size = 0;
	while (tokens_array[size])
		size++;
	new_tokens_array = ft_calloc(size + 2, sizeof(t_token *));
	if (!new_tokens_array)
		return (NULL);
	i = -1;
	while (++i < size)
		new_tokens_array[i] = tokens_array[i];
	free(tokens_array);
	new_tokens_array[i] = new_token;
	new_tokens_array[i + 1] = NULL;
	return (new_tokens_array);
}

/*	This function handles freeing a job. HUOM: the tokens should be freed
	separately, so in the job we only free the token_array and not the individual
	tokens inside it. MORE TO COME!*/
void	process_free_process(t_process *job)
{
	free(job->tokens_array);
}
