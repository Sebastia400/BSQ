##
## EPITECH PROJECT, 2021
## d10
## File description:
## description
##

OBJ = $(SRCS_C:.c=.o)

LIB = -L./lib/my -lmy

SRC		=	 sources/

SRC_C	=	bsq.c					\
			bsq_2.c					\
			my_getnbr.c				\
			my_strlen.c
			
SRCS_C	= 	$(addprefix $(SRC), $(SRC_C))

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