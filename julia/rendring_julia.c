#include "../fractol.h"

void my_put_pixel_julia(int row, int column, t_image image, int color)
{
    int bytes_per_pixel = image.bits_pp / 8;
    int offset = (column * image.ll) + (row * bytes_per_pixel);
    *(unsigned int *)(image.addr_p + offset) = color;
}

void init_julia_constants(t_com *c, t_mlx *set)
{
    c->r_part = set->julia_real;
    c->i_part = set->julia_imag;
}

void map_to_complex_plane(t_com *z, int row, int column, t_mlx *set)
{
    z->r_part = rescale_window(row, range(-2, 2), range(0, W)) * set->zoom_factor + set->move_row;
    z->i_part = rescale_window(column, range(2, -2), range(0, H)) * set->zoom_factor + set->move_column;
}

void iterate_julia(t_com *z, t_com *c)
{
    double z_r_squared = z->r_part * z->r_part;
    double z_i_squared = z->i_part * z->i_part;
    double new_z_r = z_r_squared - z_i_squared + c->r_part;
    double new_z_i = 2 * z->r_part * z->i_part + c->i_part;
    z->r_part = new_z_r;
    z->i_part = new_z_i;
}

int check_escape_and_color(t_com *z, int i, int row, int column, t_mlx *set)
{
    double	magnitude_squared;
    int		color;
    magnitude_squared = z->r_part * z->r_part + z->i_part * z->i_part;
    if (magnitude_squared > 4.0)
    {
        color = rescale_window(i, range(COLOR_BLACK, COLOR_BRIGHT_RED),
			range(0, set->pixel_loop));
        my_put_pixel(row, column, set->image, color);
        return (1);
    }
    return (0);
}

static void process_pixel(int row, int column, t_mlx *set, t_com *c)
{
    t_com	z;
    int		i;
    
	i = 0;
    map_to_complex_plane(&z, row, column, set); 
    while (i < set->pixel_loop)
    {
        if (check_escape_and_color(&z, i, row, column, set))
            return;       
        iterate_julia(&z, c);
        i++;
    }
    my_put_pixel_julia(row, column, set->image, COLOR_BLACK);
}

void render_julia(t_mlx *set)
{
    t_com	c;
    int		row;
	int		column;
    
    init_julia_constants(&c, set);
    column = 0;
    while (column < H)
    {
        row = 0;
        while (row < W)
        {
            process_pixel(row, column, set, &c);
            row++;
        }
        column++;
    }    
    mlx_put_image_to_window(set->init_c, set->window, set->image.image_ptr, 0, 0);
}
