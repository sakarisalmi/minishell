# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssalmi <ssalmi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 10:03:33 by ssalmi            #+#    #+#              #
#    Updated: 2023/06/07 14:53:26 by ssalmi           ###   ########.fr        #
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

BUILTIN_DIR = builtin/
BUILTIN_FILES = check_for_builtin echo pwd env cd exit export export_utils1 \
				unset

PARSER_DIR = parser/
PARSER_FILES = ft_funcs minishell_parser read_line_split rl_split_utils1 \
				rl_split_utils2 tokens_creator token_unpacker \
				token_unpacker_get_var token_unpacker_utils1 token_lst_utils1 \
				parser_clean_up

TOKENIZER_DIR = tokenizer/
TOKENIZER_FILES = tokenizer tokenizer_set_token_args tokenizer_error_msg

EXECUTOR_DIR = executor/
EXECUTOR_FILES = executor process_utils1 handle_redirs handle_redirs_utils1 \
				handle_redirs_utils2 handle_redirs_utils3 fds_array_utils1 \
				fds_array_utils2 executor_cmd_utils1 executor_utils1 \
				executor_utils2 executor_clean_up

MISC_DIR = misc/
MISC_FILES = minishell minishell_env_setup str_array_utils1 ft_strncmp_casein \
			minishell_loop_clean_up signal_utils1 signal_utils2 ms_funcs

FILES += $(addprefix $(BUILTIN_DIR), $(BUILTIN_FILES))
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
		@mkdir -p $(OBJS_DIR)$(BUILTIN_DIR)
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