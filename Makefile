# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 13:21:52 by tbouma            #+#    #+#              #
#    Updated: 2022/04/20 15:32:57 by tbouma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
OBJFILES := obj/pipex.o obj/utils.o obj/childs.o
LIBFT := libft/libft.a
HEADERS := -I libft/
CFLAGS := -Wall -Wextra -Werror -fsanitize=address -g
CC := gcc

all: $(LIBFT) $(NAME)

$(LIBFT): 
	make -C ./libft

$(NAME): $(OBJFILES)
	cp $(LIBFT) $(NAME)
	$(CC) $(CFLAGS) $(OBJFILES) $(LIBFT) $(HEADERS) -o $(NAME) 

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJFILES)

fclean:	clean
	rm -f $(NAME)

re: fclean all

relibft:
	make re -C ./libft

re_all: relibft re

.PHONY: clean all fclean re relibft re_all
