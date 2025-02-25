#include "../fractol.h"

int handle_keypress(int keycode, t_mlx **set)
{
    if (keycode == 53) // ESC key on MacOS
    {
        printf("ESC key pressed. Closing window...\n");
        mlx_destroy_window((*set)->init_c, (*set)->window);
        atexit(l);
        exit(0);
    }
    if (keycode == 69) 
        (*set)->pixel_loop += 10;
    if (keycode == 78)
        (*set)->pixel_loop -= 10;

    if (keycode == 123)
        (*set)->move_row += 0.5;
    if (keycode == 124)
        (*set)->move_row -= 0.5;
    if (keycode == 125)
        (*set)->move_column += 0.5;
    if (keycode == 126)
        (*set)->move_column -= 0.5;
    rendring(*set);  
    return (0);
}

int handle_mouse_enter(int b, int x, int y, t_mlx **set)
{
    double mouse_x_fractal = rescale_window(x, -2, 2, 0, W) * (*set)->zoom_factor + (*set)->move_row;
    double mouse_y_fractal = rescale_window(y, 2, -2, 0, H) * (*set)->zoom_factor + (*set)->move_column;
    if (b == 5) // Zoom out
    {
        (*set)->zoom_factor *= 0.95;
    }
    else if (b == 4) // Zoom in
    {
        (*set)->zoom_factor *= 1.05;
    }
    (*set)->move_row = mouse_x_fractal - rescale_window(x, -2, 2, 0, W) * (*set)->zoom_factor;
    (*set)->move_column = mouse_y_fractal - rescale_window(y, 2, -2, 0, H) * (*set)->zoom_factor;

    // Re-render the image
    rendring(*set);
    return (0);
}


int handle_destroy(t_mlx **set)
{
    (void)set;
    printf("Window closed.\n");
    mlx_destroy_window((*set)->init_c, (*set)->window);
    exit(0);
}


void load_event_listeners(t_mlx **set)
{
    mlx_hook((*set)->window, 2, 0, handle_keypress, set);
    mlx_hook((*set)->window, 17, 0, handle_destroy, set);   
    // mlx_hook((*set)->window, 6, 0, handle_mouse_enter, set); 
    // mlx_hook((*set)->window, 8, 0, handle_mouse_leave, set);
    mlx_mouse_hook((*set)->window, handle_mouse_enter, set); 
}