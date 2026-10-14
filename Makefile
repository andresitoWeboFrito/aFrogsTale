NAME = aFrogsTale

CC = gcc
FLAGS = -Wall -Wextra -Iinclude
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

SRC = src/main.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ $(CC) $(OBJ) $(LIBS) -o $(NAME)

%.o : %.c
	@ $(CC) $(FLAGS) -c $< -o $@

clean:
	@ rm -f $(OBJ)

fclean: clean
	@ rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
