NAME := so_long
CC := gcc
CFLAGS := -g3 -Wall -Wextra -Werror -I./minilibx-linux -Imlx_linux -O3 -c
SRC_FILES := src/main.c src/get_next_line.c src/get_next_line_utils.c
OBJ_FILES = $(SRC_FILES:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -Lmlx_linux -lmlx_Linux -L./minilibx-linux -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJ_FILES) $(NAME)

fclean: clean
	rm -rf all

re: fclean all