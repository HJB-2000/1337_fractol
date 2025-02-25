#include "../fractol.h"

void initialize_burning_ship(t_mlx *_set)
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
    _set->image.addr_p = _malloc(0, mlx_get_data_addr(_set->image.image_ptr, &_set->image.bits_pp,
                                                        &_set->image.ll, &_set->image.endian), false, false);                                
}
int animate(t_mlx *set)
{
    set->time += 0.2;
    render_ship(set);
    mlx_put_image_to_window(set->init_c, set->window, set->image.image_ptr, 0, 0); // Display the updated image
    return (0);
}
void drawing_burning_ship(char *title)
{  
    t_mlx   *set;

    set = _malloc(sizeof(t_mlx), NULL, false, false);
    set->title = title;
    set->esacap_check = 4;
    set->pixel_loop = 50;
    set->move_row = 0;
    set->move_column = 0;
    set->zoom_factor = 1;
    set->time = 0.00;
    initialize_burning_ship(set);
    render_burning_ship(set);
    // render_ship(set);
    load_event_listeners_burnig_ship(&set);
    // mlx_loop_hook(set->init_c, animate, set);
    mlx_loop(set->init_c);
}