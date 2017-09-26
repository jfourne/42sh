# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hdelaby <hdelaby@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/05 13:43:29 by hdelaby           #+#    #+#              #
#    Updated: 2017/06/20 10:07:22 by hdelaby          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh
CC = gcc
CFLAGS = -Wall -Wextra -Werror

LIBDIR = libft/
LIBNAME  = libft/libft.a
LIBFLAGS = -Llibft -lft -ltermcap

INC= -I./includes -I./libft/includes

SRC_PATH = srcs/
VPATH = .: srcs/line_edition srcs/parsing srcs/lexer srcs/execution \
	srcs/builtins srcs

SRC_NAME = main.c \
		   manip_env.c \
		   error_handling.c \
		   history_file.c \
		   init_shell.c \
		   \
		   line_edition.c \
		   term_mode.c \
		   read_input.c \
		   ft_putc.c \
		   cursor_motion.c \
		   cursor_motion_extra.c \
		   ft_getwinsz.c \
		   get_startpos.c \
		   input_keys.c \
		   history.c \
		   cutpaste.c \
		   set_curpos.c \
		   autocompletion.c \
		   autocmp_args.c \
		   autocmp_cmd.c \
		   print_col.c \
		   edition_loop.c \
		   \
		   lexer.c \
		   lexer_special.c \
		   lexer_inhibitors.c \
		   token_tools.c \
		   lexer_redirections.c \
		   lexer_tools.c \
		   complete_command.c \
		   ft_tokdel.c \
		   \
		   int_reverse.c \
		   ft_strndup_bs.c \
		   check_quote_end.c \
		   replace_backquote.c \
		   exclamation_replace.c \
		   exclamation_replace_it.c \
		   exclamation_replace_nb.c \
		   exclamation_replace_arg.c \
		   exclamation_replace_check.c \
		   ft_check_replace.c \
		   check_replace_others.c \
		   check_replace_quote.c \
		   check_backslash.c \
		   check_replace_backquote.c \
		   handle_hdoc.c \
		   \
		   ast.c \
		   ast2.c \
		   ast_command.c \
		   ast_pipe.c \
		   ast_and_or.c \
		   ast_utils.c \
		   error.c \
		   redirections.c \
		   utils.c \
		   parsing.c \
		   ft_astdel.c \
		   \
		   pipe_execution.c \
		   command_execution.c \
		   redirection.c \
		   input_redirection.c \
		   output_redirection.c \
		   browser.c \
		   exec_utils.c \
		   exec_utils2.c \
		   \
		   bi_cd.c \
		   bi_cd_extra.c \
		   bi_echo.c \
		   bi_env.c \
		   bi_exit.c \
		   bi_setenv.c \
		   bi_unsetenv.c \
		   bi_history.c \
		   bi_export.c \
		   bi_unset.c \
		   bi_history_extra.c

OBJ_PATH = obj/
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))

all: $(NAME)

run: all
	@make run -C unit_test

$(NAME): $(OBJ)
	@make all -C libft
	@$(CC) $(LIBFLAGS) $(INC) -o $@ $^ -g
	@echo "\033[32m$(NAME) created successfully\033[0m"

$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -sC libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBNAME)

re: fclean all

.NOTPARALLEL: re
	.PHONY: all clean fclean re
