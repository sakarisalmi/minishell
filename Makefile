# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 10:03:33 by ssalmi            #+#    #+#              #
#    Updated: 2023/05/02 16:59:53 by ssalmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
LIBRARY = minishell_library.a

INCLUDES = include/
LIBFT = libft/

CC = cc
CFLAGS = -Wall -Werror -Wextra
AR = ar rcs

#----------------------------------------------------------------------------#

SRCS_DIR = srcs/
OBJS_DIR = objs/

BUILTINS_DIR = builtins/
BUILTINS_FILES = echo pwd env

PARSER_DIR = parser/
PARSER_FILES = ft_funcs minishell_parser read_line_split rl_split_utils1 \
				rl_split_utils2 tokens_creator token_unpacker \
				token_unpacker_get_var token_unpacker_error_msg token_lst_utils1 \
				token_unpacker_pipe_and_redir

TOKENIZER_DIR = tokenizer/
TOKENIZER_FILES = tokenizer tokenizer_set_token_args tokenizer_error_msg

EXECUTOR_DIR = executor/
EXECUTOR_FILES = job_utils1

MISC_DIR = misc/
MISC_FILES = minishell str_array_utils1 signal

FILES += $(addprefix $(BUILTINS_DIR), $(BUILTINS_FILES))
FILES += $(addprefix $(PARSER_DIR), $(PARSER_FILES))
FILES += $(addprefix $(TOKENIZER_DIR), $(TOKENIZER_FILES))
FILES += $(addprefix $(EXECUTOR_DIR), $(EXECUTOR_FILES))
FILES += $(addprefix $(MISC_DIR), $(MISC_FILES))

SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

#----------------------------------------------------------------------------#

OBJSF = .cache_exists

all: $(NAME)

$(NAME): $(OBJS)
		$(MAKE) -C $(LIBFT)
		cp $(LIBFT)libft.a .
		mv libft.a $(LIBRARY)
		$(AR) $(LIBRARY) $(OBJS)
		$(CC) $(CFLAGS) -L $(HOME)/.brew/Cellar/readline/8.2.1/lib -lreadline -L. $(LIBRARY) $(SRCS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c | $(OBJSF)
		@$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJSF):
		@mkdir -p $(OBJS_DIR)
		@mkdir -p $(OBJS_DIR)$(BUILTINS_DIR)
		@mkdir -p $(OBJS_DIR)$(PARSER_DIR)
		@mkdir -p $(OBJS_DIR)$(TOKENIZER_DIR)
		@mkdir -p $(OBJS_DIR)$(EXECUTOR_DIR)
		@mkdir -p $(OBJS_DIR)$(MISC_DIR)

clean:
			make clean -C $(LIBFT)
			@rm -rf $(OBJS_DIR)
			@rm -f $(OBJSF)

fclean: clean
			rm -f $(NAME)
			rm -f $(LIBRARY)
			rm -f $(LIBFT)libft.a

re: fclean all

.PHONY: 	all clean fclean re