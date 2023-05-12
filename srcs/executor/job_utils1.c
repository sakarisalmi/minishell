/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 15:38:36 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/09 13:50:42 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/tokenizer.h"

t_job			**create_jobs_from_tokens(t_token *token_lst);
static t_job	**executor_jobs_array_add_new_job(t_job **jobs_array,
					t_job *new_job);
static t_job	*job_init_new_job(void);
static t_token	**job_tokens_array_add_new_token(t_token **tokens_array,
					t_token *new_token);
void			job_free_job(t_job *job);

/*----------------------------------------------------------------------------*/

t_job	**create_jobs_from_tokens(t_token *token_lst)
{
	t_token	*tmp_token;
	t_job	**jobs_array;
	int		i;

	jobs_array = ft_calloc(1, sizeof(t_job *));
	if (!jobs_array)
		return (NULL);
	jobs_array[0] = NULL;
	tmp_token = token_lst;
	i = 0;
	while (tmp_token)
	{
		if (jobs_array[i] == NULL)
		{
			jobs_array = executor_jobs_array_add_new_job(jobs_array,
					job_init_new_job());
		}
		if (tmp_token->type == T_PIPE)
			i++;
		else
			jobs_array[i]->tokens_array = job_tokens_array_add_new_token(
					jobs_array[i]->tokens_array, tmp_token);
		tmp_token = tmp_token->next;
	}
	return (jobs_array);
}

static t_job	**executor_jobs_array_add_new_job(t_job **jobs_array,
	t_job *new_job)
{
	t_job	**new_jobs_array;
	int		size;
	int		i;

	size = 0;
	while (jobs_array[size])
		size++;
	new_jobs_array = ft_calloc(size + 2, sizeof(t_job *));
	if (!new_jobs_array)
		return (NULL);
	i = -1;
	while (++i < size)
		new_jobs_array[i] = jobs_array[i];
	free(jobs_array);
	new_jobs_array[i] = new_job;
	new_jobs_array[i + 1] = NULL;
	return (new_jobs_array);
}

static t_job	*job_init_new_job(void)
{
	t_job	*new_job;

	new_job = malloc(sizeof(t_job));
	if (!new_job)
		return (NULL);
	new_job->tokens_array = malloc(sizeof(t_token *));
	if (!new_job->tokens_array)
		return (NULL);
	new_job->tokens_array[0] = NULL;
	new_job->fd_in = STDIN_FILENO;
	new_job->fd_out = STDOUT_FILENO;
	new_job->append_mode = 0;
	new_job->cmd_path = NULL;
	return (new_job);
}

static t_token	**job_tokens_array_add_new_token(t_token **tokens_array,
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
void	job_free_job(t_job *job)
{
	free(job->tokens_array);
}
