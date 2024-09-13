CFILES	:= src/*.c src/*/*.c
RM		:= rm -f
NAME	:= miniRT
CC		:= gcc
INCDIR	:= -I ./include -I mlx -I libft

LIB		:= libmlx.a
LIBFT	:= libft.a
LIBDIR	:= mlx/$(LIB)
LINUX_LIBDIR := linux_mlx/$(LIB)
LIBFTDIR	:= libft
LIBFTPATH	:= $(LIBFTDIR)/$(LIBFT)
CFLAGS	:= -Wall -Wextra -Werror $(INCDIR) #-fsanitize=address 
FILE ?=

GREEN = \033[0;32m
BLUE = \033[0;34m
VIOLET = \033[0;35m
BOLD = \033[1m
NC = \033[0m

all: $(NAME)

$(NAME): $(CFILES) $(LIBDIR) $(LIBFTPATH)
	@$(CC) $(CFLAGS) $(CFILES) -o $(NAME) -L mlx -lmlx -L $(LIBFTDIR) -lft -framework OpenGL -framework Appkit -D MACOS=1
	@clear
	@echo -e "$(BLUE)$(BOLD)[ ok ] $(NAME): created$(NC)"

linux: $(CFILES) $(LIBFTPATH) $(LINUX_LIBDIR)
	@$(CC) $(CFLAGS) $(CFILES) -o $(NAME) -L linux_mlx -lmlx -L $(LIBFTDIR) -lft -lXext -lX11 -lm -D LINUX=1
	@clear
	@echo -e "$(BLUE)$(BOLD)[ ok ] $(NAME): created$(NC)"

$(LIBDIR):
	@make -C mlx

$(LINUX_LIBDIR):
	@make -C linux_mlx

$(LIBFTPATH):
	@make -C $(LIBFTDIR)

clean:
	@make -C mlx clean
	@make -C $(LIBFTDIR) clean
	@clear
	@echo -e "$(VIOLET)$(BOLD)[ ok ] $^: mlx objs deleted$(NC)"
	@echo -e "$(VIOLET)$(BOLD)[ ok ] $^: libft objs deleted$(NC)"


fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(LIBDIR)
	@$(RM) $(LIBFTPATH)
	@clear
	@echo -e "$(VIOLET)$(BOLD)[ ok ] $^: mlx deleted$(NC)"
	@echo -e "$(VIOLET)$(BOLD)[ ok ] $^: libft deleted$(NC)"

run: all
	./$(NAME) $(FILE)

re: fclean all

relinux: fclean linux

rerun: re run

.PHONY: clean fclean all re run rerun
