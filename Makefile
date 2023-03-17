# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amejia <amejia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 14:12:43 by amejia            #+#    #+#              #
#    Updated: 2023/03/17 18:57:36 by amejia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = pipex

NAME_BONUS = pipex_bonus

NAME_DEBUG = pipex_debug

SRCS = ft_execchar.c main.c argv_generator.c

SRCS_BONUS = ft_execchar_bonus.c main_bonus.c argv_generator_bonus.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS = ${SRCS_BONUS:.c=.o}

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

bonus: $(NAME_BONUS)

clean: 
	rm -f $(OBJS) $(OBJS)
	make clean -C libft 

fclean: clean
	rm -f $(NAME) $(NAME_DEBUG) $(NAME_BONUS) libft/libft.a

VS_debug: CFLAGS += -D DEBUG=1
VS_debug: $(NAME_DEBUG)

$(NAME): $(OBJS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $@

$(NAME_BONUS): $(OBJS_BONUS) libft/libft.a
	$(CC) $(CFLAGS) $(OBJS_BONUS) libft/libft.a -o $@

$(NAME_DEBUG): $(SRCS) libft/libft.a
	$(CC) $(CFLAGS) -fdiagnostics-color=always -g $(SRCS) libft/libft.a -o $@

libft/libft.a:
	make -C libft

re: fclean all

.PHONY: all clean fclean re VS_debug 
