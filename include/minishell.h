/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:01:20 by ssalmi            #+#    #+#             */
/*   Updated: 2023/05/08 15:51:42 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

/*----------------------------minishell structs-------------------------------*/

typedef struct s_token
{
	int				type;
	char			*string;
	char			**args;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_parser
{
	char			*read_line;
	t_list			*rl_parts_lst;
	int				token_amount;
	t_token			*token_lst;
}	t_parser;

typedef struct s_job
{
	t_token	**tokens_array;
	int		*fd_in;
	int		*fd_out;
	int		append_mode;
	char	*cmd_path;
}	t_job;

typedef struct s_executor
{
	int		token_amount;
	t_token	*token_lst;
	int		jobs_amount;
	t_job	**jobs_array;
	int		**fds_array;
}	t_executor;

typedef struct s_data
{
	char		**envs;
	t_parser	parser;
	t_executor	executor;
	int			latest_exit_status;
}	t_data;

/*----------------------------------------------------------------------------*/

// signal.c
void		signal_handler(int signum);

// pwd.c
int			pwd(void);

// env.c
int			env(t_data *data);

// check_for_builtin.c
int			check_for_builtin(t_token **tokens_array);

// ft_funcs.c
int			ft_isspace(char c);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, size_t n);
char		*ft_strncat(char *dest, const char *src, size_t n);
void		*ft_realloc(void *ptr, size_t size);

// ft_strncmp_casein.c
int			ft_strncmp_casein(const char *s1, const char *s2, size_t n);

// str_array_add_str.c
char		**str_array_add_str(char **str_array, char *new_str);
char		**str_array_remove_str_by_index(char **str_array, int index);

// minishell_parser.c
int			test_minishell_parser(char *read_line, t_data *data);

// executor.c
int			test_executor_pre_setup(t_data *data);

#endif