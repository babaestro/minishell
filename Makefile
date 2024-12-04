# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 11:00:24 by anschmit          #+#    #+#              #
#    Updated: 2024/12/03 12:11:34 by ababa-ai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anschmit <anschmit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/10 11:00:24 by anschmit          #+#    #+#              #
#    Updated: 2024/09/12 15:18:54 by anschmit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SHELL_DIR = .

LIBFT_DIR = $(SHELL_DIR)/libft

SRC_DIR = srcs

OBJ_DIR = objs

NAME = minishell

CC = cc

CFLAGS = -Wall -Werror -Wextra -I$(LIBFT_DIR) -I$(SRC_DIR) -fPIE -fPIC

SRCS = $(addprefix $(SRC_DIR)/,helpers.c input.c main.c handle_tokens.c token_memory.c tokenize.c signal.c execute_cmd.c process_cmd.c find_cmd.c set_env.c free.c free2.c delimiter.c heredoc.c builtins/cd.c builtins/echo.c builtins/env.c builtins/pwd.c builtins/unset.c builtins/exit.c builtins/export_helpers.c builtins/export.c operators/redirections.c operators/redirect_helpers.c operators/apply_redirect.c operators/multiple_redirections.c handle_helpers.c token_helpers.c pipes.c quotes.c expand.c heredoc_helpers.c)

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

LIBFT = $(LIBFT_DIR)/libft.a

BUILTIN_OBJ_DIR = $(OBJ_DIR)/builtins

OPERATORS_OBJ_DIR = $(OBJ_DIR)/operators

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) CFLAGS="$(CFLAGS)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) $(BUILTIN_OBJ_DIR) $(OPERATORS_OBJ_DIR) 
	$(CC) $(CFLAGS) -c -o $@ $<

$(OBJ_DIR) $(BUILTIN_OBJ_DIR) $(OPERATORS_OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) -lreadline -pie

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

