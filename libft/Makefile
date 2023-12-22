CC		:= gcc
INCDIR	:= .
CFLAGS	:= -Wall -Wextra -Werror -I$(INCDIR)
NAME	:= libft.a
CFILES	:=  $(wildcard ft_*.c)
OBJECTS	:= $(patsubst %.c,%.o,$(CFILES))
LIB		:= ar -rcs
RM		:= rm -f

GREEN = \033[0;32m
BLUE = \033[0;34m
VIOLET = \033[0;35m
BOLD = \033[1m
NC = \033[0m

all: $(NAME)

$(NAME): $(OBJECTS)
	@clear
	@$(LIB) $@ $^
	@echo -e "$(BLUE)$(BOLD)[ ok ] $(NAME): created$(NC)"


bonus: $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) -c -o $@ $^
	@echo -e "$(BLUE)$(GREEN)[ ok ] $^: created$(NC)"


clean:
	@$(RM) $(OBJECTS)
	@clear

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all bonus re