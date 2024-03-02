NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = so_long.c get_next_line.c gnl_utils.c ft_split.c \
	parsing1.c parsing2.c utils1.c utils2.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c so_long.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
