NAME = philo

CC = gcc

FLAGS = -Wall -Wextra -Werror

HEADERS = philo.h

SRC = actions.c\
		clear_data.c\
		init_data.c\
		philo.c\
		print.c\
		utils.c\
		utils2.c\
		simulation.c

OBJ = $(SRC:c=o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re