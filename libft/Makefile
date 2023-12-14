CC		:= gcc
INCDIR	:= .
CFLAGS	:= -Wall -Wextra -Werror -I$(INCDIR)
NAME	:= libft.a
BCFILES	:= ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c ft_lstdelone.c ft_lstiter.c \
			ft_lstlast.c ft_lstmap.c ft_lstnew.c ft_lstsize.c
CFILES	:= ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c \
            ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c \
            ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c \
            ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
            ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			get_next_line.c get_next_line_utils.c ft_free_str_tab.c ft_strndup.c ft_split2.c ft_atof.c
OBJECTS	:= $(patsubst %.c,%.o,$(CFILES))
BOBJECTS:= $(patsubst %.c,%.o,$(BCFILES))
LIB		:= ar -rcs
RM		:= rm -f

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(LIB) $@ $^

bonus: $(NAME) ${BOBJECTS}
	@$(LIB) $(NAME) ${BOBJECTS}

%.o:%.c
	@$(CC) $(CFLAGS) -c -o $@ $^

clean:
	@$(RM) $(OBJECTS) $(BOBJECTS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean fclean all bonus re