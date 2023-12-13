CFILES	:= main.c utils.c list_utils.c colors.c events.c operations.c \
	trace_ray.c lighting.c
RM		:= rm -f
NAME	:= miniRT
CC		:= gcc
INCDIR	:= -I . -I mlx

LIB	:= libmlx.a
LIBDIR := mlx/$(LIB)
CFLAGS	:= -Wall -Wextra -Werror $(INCDIR) -fsanitize=address 
FILE ?=

all: $(NAME)

$(NAME): $(CFILES) $(LIBDIR)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME) -L mlx -lmlx -framework OpenGL -framework Appkit

$(LIBDIR):
	make -C mlx

clean:
	make -C mlx clean

fclean: clean
	$(RM) $(NAME) $(BONUS)
	$(RM) $(LIBDIR)

run: all
	./$(NAME) $(FILE)

re: fclean all

rerun: re run

.PHONY: clean fclean all re run rerun