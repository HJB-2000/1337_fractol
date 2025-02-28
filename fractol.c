#include "fractol.h"
void l()
{
    system("leaks fractol");
}
int animate(t_mlx *set)
{
    set->time += 1;
    if (set->pixel_loop == 70)
        set->pixel_loop = 50;
    if ( set->time == 10)
    {
        set->pixel_loop += 1;
        set->time = 0.0;
    }
    render_burning_ship(set);
    mlx_put_image_to_window(set->init_c, set->window, set->image.image_ptr, 0, 0); // Display the updated image
    return (0);
}
t_mlx	*create_set(t_mlx	*set, char **argv, int flag)
{
    double  v1;
    double  v2;
    char    *title;

	set = _malloc(sizeof(t_mlx), NULL, false, false);
    title = argv[1];
    if (flag == 2)
    {
        v1 = ft_atoi(argv[2]);
        v2 = ft_atoi(argv[3]);
    }
    else
        v1 = v2 = 0;
    set->flag = flag;
    set->title = title;
    set->esacap_check = 4;
    set->pixel_loop = 50;
    set->move_row = 0;
    set->move_column = 0;
    set->zoom_factor = 1;
    set->julia_real = v1;
    set->julia_imag = v2; 
    set->time = 0.00;
    return (set);
}
void	draw(int flag, char **argv)
{
	t_mlx	*set = NULL;
	set = create_set(set, argv, flag);
    initialize_set(set);
	if (flag == 1)
	{
        rendring(set);
	    load_event_listeners(&set);
	    mlx_loop(set->init_c);
	}
	else if (flag == 2)
	{
        render_julia(set);
	    load_event_listeners(&set);
        // load_event_listeners_julia(&set);
        mlx_loop(set->init_c);
	}
	else if (flag == 3)
	{
        // initialize_set(set);
        // render_burning_ship(set);
        // render_ship(set);
        load_event_listeners_burnig_ship(&set);
        mlx_loop_hook(set->init_c, animate, set);
        mlx_loop(set->init_c);
	}
}


void	treat_args(int argc, char **argv)
{
    int	drawing_flag;

	drawing_flag = 0;
	if (!ft_strncmp(argv[1], "Mandelbrot", 11))
		drawing_flag = 1;
    else if (!ft_strncmp(argv[1], "Julia", 6))
    {   
        if (argc != 4)
        {
            my_putstr("Error: Julia set requires two additional arguments.\n");
            return ;
        }
		drawing_flag = 2;
    }
	else if (!ft_strncmp(argv[1], "burning_ship", 13))
		drawing_flag = 3;
	if(drawing_flag != 0)
	{
		draw(drawing_flag, argv);
		return ;
	}
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
