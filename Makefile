CFILES	:= *.c
RM		:= rm -f
NAME	:= miniRT
CC		:= gcc
INCDIR	:= -I . -I mlx -I libft

LIB		:= libmlx.a
LIBFT	:= libft.a
LIBDIR	:= mlx/$(LIB)
LIBFTDIR	:= libft
LIBFTPATH	:= $(LIBFTDIR)/$(LIBFT)
CFLAGS	:= -Wall -Wextra -Werror $(INCDIR) #-fsanitize=address 
FILE ?=

all: $(NAME)

$(NAME): $(CFILES) $(LIBDIR) $(LIBFTPATH)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME) -L mlx -lmlx -L $(LIBFTDIR) -lft -framework OpenGL -framework Appkit -D MACOS=1

linux: $(CFILES) $(LIBFTPATH)
	$(CC) $(CFLAGS) $(CFILES) -o $(NAME) -L mlx -lmlx -L $(LIBFTDIR) -lft -lXext -lX11 -lm -D LINUX=1

$(LIBDIR):
	make -C mlx

$(LIBFTPATH):
	make -C $(LIBFTDIR)

clean:
	make -C mlx clean
	make -C $(LIBFTDIR) clean

fclean: clean
	$(RM) $(NAME) $(BONUS)
	$(RM) $(LIBDIR)
	$(RM) $(LIBFTPATH)

run: all
	./$(NAME) $(FILE)

re: fclean all

rerun: re run

.PHONY: clean fclean all re run rerun
