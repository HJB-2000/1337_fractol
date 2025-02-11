#include "fractol.h"
void l()
{
    system("leaks fractol");
}

void initialize_set(t_mlx *_set)
{
    _set->init_c = _malloc(0, mlx_init(), false, false);
    if (!_set->init_c)
        _malloc(0, NULL, false, true);
    _set->window = _malloc(0, mlx_new_window(_set->init_c, W, H, _set->title), false, false);
    if (!_set->window)
        _malloc(0, NULL, false, true);
    _set->image.image_ptr = _malloc(0, mlx_new_image(_set->init_c, W, H), false, false);
    if (!_set->image.image_ptr)
    {   
        mlx_destroy_window(_set->init_c, _set->window);
        _malloc(0, NULL, false, true);
    }
    _set->image.addr_p = mlx_get_data_addr(_set->image.image_ptr, &_set->image.bits_pp,
                                                        &_set->image.ll, &_set->image.endian);
}

void drawing(char *title)
{  
    t_mlx   *set;

    set = _malloc(sizeof(t_mlx), NULL, false, false);
    set->title = title;
    set->esacap_check = 4;
    set->pixel_loop = 42;
    initialize_set(set);
    rendring(set);
    mlx_loop(set->init_c);
}


int main(int argc, char **argv)
{
    if ((2 == argc && !ft_strncmp(argv[1], "Mandelbrot", 11))
        || (4 == argc && !ft_strncmp(argv[1], "julia", 6)))
    {
        drawing(argv[1]);
    }
    else
    {
        my_putstr("please enter a valide arguments exmples:\n\
        \t./farctol mandelbort.\n\
        \t./farctol julia <value 1><value 2>\n");
    }
    atexit(l);
    return 0;
}
