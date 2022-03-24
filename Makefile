NAME := libpipex.a
OBJFILES := obj/pipex.o
LIBFT := ./libft/libft.a
CFLAG := -Wall -Wextra -Werror

all: libft $(NAME)

libft:
	make -C ./libft

relibft:
	make re -C ./libft

$(NAME): $(OBJFILES)
	cp $(LIBFT) $(NAME)
	ar -rsc  $(NAME) $(OBJFILES)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -f $(OBJFILES)

fclean:	clean
	rm -f $(NAME)
	make fclean -C ./libft

re: fclean all

reall: relibft re

.PHONY: clean all fclean re libft relibft reall
