NAME = cub3D

CFLAGS = -Wall -Wextra -Werror -Ofast -Wno-bitwise-instead-of-logical

LINK_H = -Iinclude

OBJSFOLDER = objs/
INCLUDEFOLDER = include/

LIB = lib/lib.so

HOT_RELOAD	= $(foreach obj, $(HOT_RELOAD_FILES), $(OBJSFOLDER)$(obj))
HOT_RELOAD_H	= $(INCLUDEFOLDER)draw.h	\
			$(INCLUDEFOLDER)utils.h  \
			$(INCLUDEFOLDER)utils.h	  \
			$(INCLUDEFOLDER)vectors.h  \
			$(INCLUDEFOLDER)vectors.h   \

HOT_RELOAD_FILES = rays.o	\
			dda.o	 \
			fps.o	  \
			draw.o     \
			utils.o     \
			shapes.o     \
			draw_utils.o  \
			vect_utils1.o  \
			vect_utils2.o   \

OBJS_FILES = test.o	    \
		hooks.o	     \
		parse.o	      \
		clean_map.o    \
		clean_mlx.o     \
		line_utils.o     \
		parse_utils.o     \
		p_map_utils.o	   \
		player_utils.o	    \
		map_ds_utils.o	     \
		texture_utils.o	      \
		map_validation.o       \
		clean_textures.o        \
		validation_utils.o       \
		parse_not_utils.o	  \
		tiny_parsing_helpers.o	   \
		parse_definitely_not_utils.o\

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	LINKS = -lmlx42 # -L"$(HOME)/.brew/opt/glfw/lib/"
else
	LINKS = -lmlx42_linux -ldl -pthread -lm
endif

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))
HEADER_FILES	=	$(INCLUDEFOLDER)draw.h		\
				$(INCLUDEFOLDER)test.h	  \
				$(INCLUDEFOLDER)hooks.h	   \
				$(INCLUDEFOLDER)libft.h	    \
				$(INCLUDEFOLDER)parse.h	     \
				$(INCLUDEFOLDER)structs.h     \
				$(INCLUDEFOLDER)validation.h   \
				$(INCLUDEFOLDER)get_next_line.h	\

GLOBAL_HEADERS = include/structs.h

LIBFT = src/libft/libft.a

all: objs lib/libmlx42.a $(LIBFT) $(LIB) $(NAME)

objs:
	@mkdir objs

$(LIBFT):
	@echo "Compiling libft..."
	@make -C src/libft bonus

mlx/libmlx42.a:
	cmake -S mlx -B mlx
	make -C mlx

lib/libmlx42.a: mlx/libmlx42.a
	-mkdir lib/ 2>/dev/null
	cp mlx/libmlx42.a lib/

$(NAME): lib/libmlx42.a $(OBJS) $(LIB)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) $(LIB) -o $@ -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw

$(LIB): $(HOT_RELOAD) $(HOT_RELOAD_H)
	$(CC) $(CFLAGS) $(LIBFT) -shared $(HOT_RELOAD) -o $(LIB) -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw

$(OBJSFOLDER)%.o: src/drawing/%.c include/draw.h $(GLOBAL_HEADERS)
	$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/vects/%.c include/vectors.h $(GLOBAL_HEADERS)
	$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/validation/%.c $(GLOBAL_HEADERS)
	$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/parsing/%.c include/parse.h $(GLOBAL_HEADERS)
	$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/cleaning/%.c $(GLOBAL_HEADERS)
	$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

$(OBJSFOLDER)%.o: src/%.c $(GLOBAL_HEADERS)
	$(CC) $(CFLAGS) $(LINK_H) -c $< -o $@

re: fclean all

fclean: clean
	rm -rf $(NAME)
	make -C src/libft fclean
	rm -rf lib/*

clean:
	rm -rf $(OBJS)
	make -C src/libft clean

norm:
	norminette src/*.c include/*.h

.PHONY: all clean fclean re
