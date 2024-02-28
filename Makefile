NAME = so_long
CC = cc -g
CFLAGS = -Wall -Wextra -Werror 

SRC = so_long.c get_next_line_bonus.c gnl_utils_bonus.c ft_split.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) 
	$(CC) $(CFLAGS) $(OBJ)  -lmlx -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c so_long.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re all
