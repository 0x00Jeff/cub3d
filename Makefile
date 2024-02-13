NAME = cub3D

CFLAGS = -Wall  -Wextra -Werror -Ofast # -g -fsanitize=address

LINK_H = -Iinclude

OBJSFOLDER = objs/
INCLUDEFOLDER = include/

OBJS_FILES = test.o				\
			 hooks.o	  		 \
			parse.o			  	  \
			parse_utils.o	  	   \
			map_validation.o		\
			validation_utils.o		 \
			player_utils.o			  \
			line_utils.o			   \
			p_map_utils.o				\
			map_ds_utils.o				  \
			texture_utils.o				   \
			parse_not_utils.o				\
			parse_definitely_not_utils.o	 \
			draw.o	  \
			shapes.o	   \
			draw_utils.o	\
			rays.o			 \
			vect_utils1.o 	  \
			vect_utils2.o 	   \
			utils.o 		    \
			unused.o		     \
			clean_textures.o \
			clean_map.o \
			clean_mlx.o \
			tiny_parsing_helpers.o \
			dda.o					\
			fps.o

OS := $(shell uname -s)

ifeq ($(OS), Darwin)
	LINKS = -lmlx42 -L"$(HOME)/.brew/opt/glfw/lib/"
else
	LINKS = -lmlx42_linux -ldl -pthread -lm
endif

OBJS = $(foreach obj, $(OBJS_FILES), $(OBJSFOLDER)$(obj))
HEADER_FILES	=	$(INCLUDEFOLDER)draw.h \
					$(INCLUDEFOLDER)fps.h \
					$(INCLUDEFOLDER)get_next_line.h \
					$(INCLUDEFOLDER)hooks.h \
					$(INCLUDEFOLDER)libft.h \
					$(INCLUDEFOLDER)parse.h \
					$(INCLUDEFOLDER)structs.h \
					$(INCLUDEFOLDER)test.h \
					$(INCLUDEFOLDER)unused.h \
					$(INCLUDEFOLDER)utils.h \
					$(INCLUDEFOLDER)validation.h \
					$(INCLUDEFOLDER)vectors.h

GLOBAL_HEADERS = include/structs.h

LIBFT = src/libft/libft.a

all: objs $(LIBFT) $(NAME)

objs:
	@mkdir objs

$(LIBFT):
	@echo "Compiling libft..."
	@make -C src/libft bonus

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBFT) -o $@ -L`pwd`/lib $(LINKS) $(LINK_H) -lglfw

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
	make -C src/libft clean

clean:
	rm -rf $(OBJS)
	make -C src/libft fclean

norm:
	norminette src/*.c include/*.h

.PHONY: all clean fclean re
