# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amejia <amejia@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/14 14:12:43 by amejia            #+#    #+#              #
#    Updated: 2023/03/08 17:12:19 by amejia           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

NAME_DEBUG = pipex_debug

SRCS = ft_execchar.c main.c

OBJS = ${SRCS:.c=.o}

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

clean: 
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(NAME_DEBUG)

VS_debug: CFLAGS += -D DEBUG=1
VS_debug: $(NAME_DEBUG)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $@

$(NAME_DEBUG): $(SRCS)
	$(CC) $(CFLAGS) -fdiagnostics-color=always -g $(SRCS) libft/libft.a -o $@


re: fclean all

.PHONY: all clean fclean re VS_debug 
