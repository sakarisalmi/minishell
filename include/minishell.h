/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 10:01:20 by ssalmi            #+#    #+#             */
/*   Updated: 2023/04/24 15:28:39 by ssalmi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libft/libft.h"

/*----------------------------minishell structs-------------------------------*/

typedef struct s_token
{
	int				type;
	char			*string;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_parser
{
	char			*read_line;
	t_list			*rl_parts_ls;
	int				token_amount;
	t_token			*token_ls;
}	t_parser;

typedef struct s_data
{
	char		**envs;
	t_parser	parser;
}	t_data;

/*----------------------------------------------------------------------------*/

// pwd.c
int			pwd(void);

// env.c
int			env(t_data *data);

// ft_funcs.c
int			ft_isspace(char c);
char		*ft_strcpy(char *dest, const char *src);
char		*ft_strncpy(char *dest, const char *src, size_t n);
char		*ft_strncat(char *dest, const char *src, size_t n);
void		*ft_realloc(void *ptr, size_t size);

// minishell_parser.c
int			minishell_parser(char *read_line, t_data *data);

#endif