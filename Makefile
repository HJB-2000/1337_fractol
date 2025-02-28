NAME = fractol
HEADER = fractol.h

SRC_FILES = fractol_helper_func.c\
			my_malloc.c\
			mandlbrot/rendring_mandelbrot.c\
			mandlbrot/z_math.c\
			mandlbrot/events.c\
			julia/rendring_julia.c\
			julia/julia_events.c\
			bonus/render_burning_ship.c\
			bonus/burning_ship_events.c\
			initialize_set.c\
			fractol.c

OBJS = $(SRC_FILES:.c=.o)


CFLAGS = -Werror -Wall -Wextra
CC = cc
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ 

$(NAME) : $(OBJS)
	$(CC) $(GFLAGS) $(OBJS) -o $(NAME) -lmlx -framework OpenGL -framework AppKit
all: $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f fractol
re: fclean all
