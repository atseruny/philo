CC = cc
NAME = philo
CFLAGS = -Wall -Wextra #-Werror

SRC = main.c ft_atoi.c start.c routine.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) philo.h Makefile
	$(CC) $(OBJ) -o $(NAME) -g3 -fsanitize=thread

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
