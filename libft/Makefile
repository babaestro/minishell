# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ababa-ai <ababa-ai@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/26 11:09:20 by ababa-ai          #+#    #+#              #
#    Updated: 2024/06/10 13:09:33 by ababa-ai         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -fPIC

SRCS = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
ft_memmove.c ft_memset.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
ft_strlen.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c \
ft_strtrim.c ft_split.c ft_calloc.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_split.c \
ft_strmapi.c ft_striteri.c ft_itoa.c ft_putnbr_fd.c \
get_next_line_bonus.c ft_unsigned_or_pointer.c ft_printf.c ft_basic_utils.c ft_puthex.c

OBJS = $(SRCS:.c=.o)

NAME = libft.a

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean:
	@rm -f $(OBJS) $(NAME)

re: fclean all
