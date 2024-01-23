NAME = cub3D

CFLAGS = -Wall -Wextra -Werror # -g -fsanitize=address

LINK_H = -Iinclude

OBJSFOLDER = objs/

LIB = lib/lib.so

OBJS_FILES = test.o \
			 hooks.o \

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	LINKS = -lmlx42 -L"$(HOME)/.brew/opt/glfw/lib/"
else
	LINKS = -lmlx42_linux -ldl -pthread -lm
endif

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))

GLOBAL_HEADERS = include/structs.h

all: objs $(NAME)

objs:
	@mkdir objs

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(CFLAGS) -o $@ -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw

$(LIB): objs/draw.o
	$(CC) $(CFLAGS) $(OBJS) -shared $< -o $(LIB) -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw

$(OBJSFOLDER)%.o: src/%.c #include/%.h $(GLOBAL_HEADERS)
	$(CC) $(CFLAGS) -fPIC $(LINK_H) -c $< -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME) $(LIB)

clean:
	rm -rf $(OBJS)

norm:
	norminette src/*.c include/*.h

.PHONY: all clean fclean re
