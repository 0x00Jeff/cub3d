NAME = cub3D

CFLAGS = -Wall -Wextra -Werror # -g -fsanitize=address

LINK_H = -Iinclude

OBJSFOLDER = objs/

OBJS_FILES = test.o \
			 hooks.o \
			 draw.o


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

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o $@ -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw

$(OBJSFOLDER)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(LINK_H)

$(OBJSFOLDER)%.o: src/%.c #include/%.h $(GLOBAL_HEADERS)
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME)

clean:
	rm -rf $(OBJS)

norm:
	norminette src/*.c include/*.h

.PHONY: all clean fclean re
