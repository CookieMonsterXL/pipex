# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbouma <tbouma@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/25 13:21:52 by tbouma            #+#    #+#              #
#    Updated: 2022/04/22 13:06:48 by tbouma           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := pipex
OBJFILES := obj/pipex.o obj/utils.o obj/childs.o
LIBFT := libft/libft.a
HEADERS := -I libft/
CFLAGS := -Wall -Wextra -Werror
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
	make clean -C ./libft

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

.PHONY: clean all fclean re
