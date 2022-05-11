##
## EPITECH PROJECT, 2021
## d10
## File description:
## description
##

OBJ = $(SRC:.c=.o)

SRC	=		main.c					\
			save_map.c				\
			map_size.c				\
			find_bsq.c				\
			print_map.c				\
			my_getnbr.c				\
			my_strlen.c

CFLAGS = -I./include

NAME = bsq

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:	fclean all
	make clean
