CC=cc

CFLAGS=-Wall -Wextra -Werror -Imlx -g -ggdb3 -fsanitize=address

NAME = cub3D

SRC = test.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	norminette *.c

.PHONY: all clean fclean re
