NAME := pipex
SRCFILES := pipex.c utils.c childs.c
LIBFT := ./libft/libft.a
CFLAG := -Wall -Wextra -Werror #-fsanitize=address -g

all: libft $(NAME)

libft:
	make -C ./libft

relibft:
	make re -C ./libft

$(NAME): $(SRCFILES)
	cp $(LIBFT) $(NAME)
	gcc  $(SRCFILES) $(CFLAG) $(LIBFT) -o $(NAME) 

clean:
	rm -f $(NAME)

fclean:	clean
	rm -f $(NAME)

re: fclean all

reall: relibft re

.PHONY: clean all fclean re libft relibft reall
