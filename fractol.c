#include "fractol.h"
void l()
{
    system("leaks fractol");
}



void	treat_args(int argc, char **argv)
{
	if (!ft_strncmp(argv[1], "Mandelbrot", 11))
		drawing_mandlbrot("Mandelbrot");
	

    else if (!ft_strncmp(argv[1], "Julia", 6))
    {   
        if (argc != 4)
        {
            my_putstr("Error: Julia set requires two additional arguments.\n");
            return ;
        }
        drawing_julia("Julia", ft_atoi(argv[2]), ft_atoi(argv[3]));
    }
	else if (!ft_strncmp(argv[1], "burning_ship", 13))
		drawing_burning_ship("burning_ship");
    else
         my_putstr("please enter a valide arguments exmples:\n\
        \t./fractol Mandelbrot\n\
        \t./fractol Julia <value 1><value 2>\n");
}
int main(int argc, char **argv)
{
   
    if (argc < 2 || !argv[1])
    {
        my_putstr("Error: Missing fractal type argument.\n");
        return 1;
    }
    if (argc == 2 || argc == 4)
    {
        treat_args(argc, argv);
    }
    else
        my_putstr("please enter a valide arguments exmples:\n\
        \t./fractol Mandelbrot\n\
        \t./fractol Julia <value 1><value 2>\n");

    atexit(l);
    return 0;
}
