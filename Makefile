##
## EPITECH PROJECT, 2025
## Panoramix [WSL: Ubuntu]
## File description:
## Makefile
##

CC ?= gcc
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

SRC = src/main.c

OBJ = $(SRC:.c=.o)

NAME = panoramix

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
