#include "../fractol.h"

int handle_keypress_b(int keycode, t_mlx **set)
{
    if (keycode == 53)
    {
        printf("ESC key pressed. Closing window...\n");
        mlx_destroy_window((*set)->init_c, (*set)->window);
        atexit(l);
        exit(0);
    }
    if (keycode == 69) 
        (*set)->pixel_loop += 50;
    if (keycode == 78)
        (*set)->pixel_loop -= 50;
    render_burning_ship(*set);  
    // render_ship(*set);

    return (0);
}

int handle_mouse_enter_b(int b, int x, int y, t_mlx **set)
{
    if (!set || !*set)
        return 0;
    double mouse_x_fractal = rescale_window(x, -2, 2, 0, W) * (*set)->zoom_factor + (*set)->move_row;
    double mouse_y_fractal = rescale_window(y, 2, -2, 0, H) * (*set)->zoom_factor + (*set)->move_column;
    if (b == 5)
    {
        (*set)->zoom_factor *= 0.95;
    }
    else if (b == 4)
    {
        (*set)->zoom_factor *= 1.05;
    }
    (*set)->move_row = mouse_x_fractal - rescale_window(x, -2, 2, 0, W) * (*set)->zoom_factor;
    (*set)->move_column = mouse_y_fractal - rescale_window(y, 2, -2, 0, H) * (*set)->zoom_factor;
    render_burning_ship(*set);
    // render_ship(*set);
    return (0);
}

int handle_destroy_b(t_mlx **set)
{
    (void)set;
    printf("Window closed.\n");
    mlx_destroy_window((*set)->init_c, (*set)->window);
    exit(0);
}

void load_event_listeners_burnig_ship(t_mlx **set)
{
    mlx_hook((*set)->window, 2, 0, handle_keypress_b, set);
    // mlx_hook((*set)->window, 2, 0, handle_keypress_j_2, set);
    mlx_hook((*set)->window, 17, 0, handle_destroy_b, set);   
    // mlx_hook((*set)->window, 6, 0, handle_mouse_enter, set); 
    // mlx_hook((*set)->window, 8, 0, handle_mouse_leave, set);
    mlx_mouse_hook((*set)->window, handle_mouse_enter_b, set); 
}