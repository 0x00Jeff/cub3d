NAME = cub3D

CFLAGS = -Wall -Wextra -Werror # -g -ggdb3 # -O3 -fsanitize=address

LINK_H = -Iinclude

OBJSFOLDER = objs/
INCLUDEFOLDER = include/

LIB = lib/lib.so

HOT_RELOAD_FILES = draw.o \
				vect_utils1.o \
				vect_utils2.o \
				utils.o \
				unused.o

HOT_RELOAD		= $(foreach obj, $(HOT_RELOAD_FILES), $(OBJSFOLDER)$(obj))
HOT_RELOAD_H	= $(INCLUDEFOLDER)draw.h \
					$(INCLUDEFOLDER)vectors.h \
					$(INCLUDEFOLDER)utils.h \
					$(INCLUDEFOLDER)unused.h

OBJS_FILES = test.o \
			 hooks.o

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	LINKS = -lmlx42 -L"$(HOME)/.brew/opt/glfw/lib/"
else
	LINKS = -lmlx42_linux -ldl -pthread -lm
endif

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))

GLOBAL_HEADERS = include/structs.h

LIBFT = src/libft/libft.a

#all: objs $(LIBFT) $(NAME)
all: objs $(NAME)

objs:
	@mkdir objs

$(LIBFT):
	@echo "Compiling libft..."
	@make -C src/libft

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(CFLAGS) -o $@ -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw
	#$(CC) $(OBJS) $(CFLAGS) $(LIBFT) -o $@ -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw

$(LIB): $(HOT_RELOAD) $(HOT_RELOAD_H)
	$(CC) $(CFLAGS) -shared $(HOT_RELOAD) -o $(LIB) -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw

$(OBJSFOLDER)%.o: src/%.c $(GLOBAL_HEADERS)
	$(CC) $(CFLAGS) -fPIC $(LINK_H) -c $< -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME) $(LIB)
	make -C src/libft clean

clean:
	rm -rf $(OBJS) $(HOT_RELOAD)
	make -C src/libft fclean

norm:
	norminette src/*.c include/*.h

.PHONY: all clean fclean re
