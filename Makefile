# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 13:21:52 by tbouma            #+#    #+#              #
#    Updated: 2022/03/25 13:44:56 by tbouma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
SRCFILES := pipex.c utils.c childs.c
LIBFT := ./libft/libft.a
CFLAG := -Wall -Wextra -Werror

all: libft $(NAME)

libft:
	make -C ./libft

relibft:
	make re -C ./libft

$(NAME): $(SRCFILES)
	cp $(LIBFT) $(NAME)
	$(CC)  $(SRCFILES) $(CFLAG) $(LIBFT) -o $(NAME) 

clean:
	rm -f $(NAME)

fclean:	clean
	rm -f $(NAME)

re: fclean all

reall: relibft re

.PHONY: clean all fclean re libft relibft reall
