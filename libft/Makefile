CC		:= gcc
INCDIR	:= .
CFLAGS	:= -Wall -Wextra -Werror -I$(INCDIR)
NAME	:= libft.a
CFILES	:=  $(wildcard ft_*.c)
OBJECTS	:= $(patsubst %.c,%.o,$(CFILES))
LIB		:= ar -rcs
RM		:= rm -f

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(LIB) $@ $^

bonus: $(NAME)

%.o:%.c
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@$(RM) $(OBJECTS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all bonus re