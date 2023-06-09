/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:01:20 by ssalmi            #+#    #+#             */
/*   Updated: 2023/06/12 14:58:31 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

/*----------------------------minishell structs-------------------------------*/

typedef struct s_envs_set_up_func
{
	char	**minishell_env;
	int		shlvl_int;
	char	*shlvl_str;
	int		i;
}	t_envs_set_up_func;

typedef struct s_envs_set_up_shlvl_func
{
	int		shlvl_int;
	char	*shlvl_str;
	char	*str_to_return;
	int		i;
}	t_envs_set_up_shlvl_func;

typedef struct s_token
{
	int				type;
	char			*string;
	char			*rl_part_string;
	char			**args;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_parser
{
	t_list	*rl_parts_lst;
	int		token_amount;
	t_token	*token_lst;
}	t_parser;

typedef struct s_process
{
	t_token	**tokens_array;
	int		fd_in;
	int		fd_out;
	char	*cmd_path;
	int		last_here_doc;
}	t_process;

typedef struct s_executor
{
	int			token_amount;
	t_token		*token_lst;
	int			process_amount;
	t_process	**process_array;
	int			**fds_array;
	int			**here_doc_array;
}	t_executor;

typedef struct s_data
{
	char		**envs;
	t_parser	parser;
	t_executor	executor;
	int			latest_exit_status;
}	t_data;

/*----------------------------------------------------------------------------*/

// the global variable for signals (especially here_doc)
int		g_in_here_doc;

// signal_utils1.c
void	signal_handler(int signum);
void	ctrl_d_handler(void);
void	turnoff_echo(struct termios *termios);
void	turnon_echo(struct termios *termios);
int		get_signals(t_data *data);

// signal_utils2.c
void	here_doc_signal(int signum);

// ft_funcs.c
int		ft_isdigit(int c);
int		ft_isspace(char c);
char	*ft_strcpy(char *dest, const char *src);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char	*ft_strncat(char *dest, const char *src, size_t n);
void	*ft_realloc(void *ptr, size_t size);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);

// ft_strncmp_casein.c
int		ft_strncmp_casein(const char *s1, const char *s2, size_t n);

// str_array_add_str.c
char	**str_array_add_str(char **str_array, char *new_str);
char	**str_array_remove_str_by_index(char **str_array, int index);
void	str_array_free_everything(char **str_array);

// minishell_parser.c
int		minishell_parser(char *read_line, t_data *data);
void	rl_replace_line(const char *text, int clear_undo);

// executor.c
int		test_executor_pre_setup(t_data *data);
int		real_executor_pre_setup(t_data *data);

// minishell_loop_clean_up.c
void	minishell_loop_clean_up(t_data *data);

// minishell.c
int		minishell_sig_hand_err_msg(t_data *data);

// minishell_env_setup.c
char	**minishell_env_setup(char **envp);

// ms_funcs.c
void	*ms_calloc(size_t count, size_t size, t_data *data);
void	*ms_realloc(void *ptr, size_t size, t_data *data);
void	minishell_fatal_error_exit(t_data *data);

#endif