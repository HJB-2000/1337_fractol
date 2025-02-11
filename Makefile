NAME = fractol
HEADER = fractol.h

SRC_FILES = fractol_helper_func.c\
			fractol_helper_func_1.c\
			my_malloc.c\
			rendring.c\
			z_math.c\
			fractol.c

OBJS = $(SRC_FILES:.c=.o)


CFLAGS = -Werror -Wall -Wextra
CC = cc
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME) -lmlx -framework OpenGL -framework AppKit 
all: $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f fractol
re: fclean all
