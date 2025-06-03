CC = cc
NAME = philo_bonus
CFLAGS = -Wall -Wextra -Werror

SRC = main.c ft_atol.c utils.c start.c routine.c actions.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) philo_bonus.h Makefile
	$(CC) $(OBJ) -o $(NAME) 
# -g3 -fsanitize=address

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
