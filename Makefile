INC=%%%%

INCLIB=$(INC)/../lib

UNAME := $(shell uname)

CFLAGS= -I$(INC) -O3 -I.. -g

NAME= so_long

SRC = main.c main_utl.c nextline/get_next_line.c nextline/get_next_line_utils.c so_long_utl.c print/ft_printf.c print/ft_printf_fun.c print/ft_printf_util.c so_long.c error.c

OBJ = $(SRC:%.c=%.o)

LFLAGS = -L.. -lmlx -L$(INCLIB) -lXext -lX11 -lm

ifeq ($(UNAME), Darwin)
	# mac
	CC = clang
else ifeq ($(UNAME), FreeBSD)
	# FreeBSD
	CC = clang
else
	#Linux and others...
	CC	= cc
	LFLAGS += -lbsd
endif

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LFLAGS)
    
clean:
	rm -f $(NAME) $(OBJ) *~ core *.core
fclean:		clean
					rm -rf $(NAME)
	
re: clean all

.PHONY: all clean fclean re

