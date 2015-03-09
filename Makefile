NAME =	Layout

SRC =	./main.c\
	./display.c\
	./init.c\
	./input.c\
	./colors.c\
	./tools.c\
	./files.c\
	./ui.c\
	./html.c\

OBJ =	$(SRC:.c=.o)

FLAG =	-Wall -Werror -Wextra

LIB =	./libft/libft.a

MLX =	-L/usr/X11/lib -lmlx -lXext -lX11

all: $(NAME)
$(NAME):
	@make -C ./libft
	@gcc $(FLAG) -O3 -c $(SRC)
	@gcc $(LIB) $(OBJ) -o $(NAME) $(MLX)

clean:
	@rm -f $(OBJ)
fclean:	clean
	@rm -f $(NAME)

re: fclean all
	@rm *.o
