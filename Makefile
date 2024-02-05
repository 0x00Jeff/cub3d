NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -O3 # -g -ggdb3 -fsanitize=address

LINK_H = -Iinclude

OBJSFOLDER = objs/
INCLUDEFOLDER = include/

LIB = lib/lib.so

HOT_RELOAD_FILES = draw.o \
				vect_utils1.o \
				vect_utils2.o

HOT_RELOAD		= $(foreach obj, $(HOT_RELOAD_FILES), $(OBJSFOLDER)$(obj))
HOT_RELOAD_H	= $(INCLUDEFOLDER)draw.h \
					$(INCLUDEFOLDER)vectors.h

#HOT_RELOAD		= $(foreach obj, $(HOT_RELOAD_FILES), $(OBJSFOLDER)$(obj))
#HOT_RELOAD_H	= $(foreach obj, $(HOT_RELOAD_FILES), $(INCLUDEFOLDER)$(obj:.o=.h))

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

all: objs $(NAME)

objs:
	@mkdir objs

$(NAME): $(OBJS) $(LIB)
	$(CC) $(OBJS) $(CFLAGS) -o $@ -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw

$(LIB): $(HOT_RELOAD) $(HOT_RELOAD_H)
	$(CC) $(CFLAGS) -shared $(HOT_RELOAD) -o $(LIB) -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw

$(OBJSFOLDER)%.o: src/%.c $(GLOBAL_HEADERS)
	$(CC) $(CFLAGS) -fPIC $(LINK_H) -c $< -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME) $(LIB)

clean:
	rm -rf $(OBJS) $(HOT_RELOAD)

norm:
	norminette src/*.c include/*.h

.PHONY: all clean fclean re
