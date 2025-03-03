#include "../fractol.h"

void initialize_z_and_c(t_com *z, t_com *c, int row, int column, t_mlx *set)
{
    z->r_part = rescale_window(row, range(-2, 2), range(0, W))
		* set->zoom_factor + set->move_row;
    z->i_part = rescale_window(column, range(2, -2), range(0, H))
		* set->zoom_factor + set->move_column;
    c->r_part = z->r_part;
    c->i_part = z->i_part;
}

void calculate_new_z(t_com *z, t_com *c)
{
	double z_r_abs;
	double z_i_abs;
	double new_z_r;
	double new_z_i;

    z_r_abs = fabs(z->r_part);
    z_i_abs = fabs(z->i_part);
    new_z_r = z_r_abs * z_r_abs - z_i_abs * z_i_abs + c->r_part;
    new_z_i = 2 * z_r_abs * z_i_abs + c->i_part;
    z->r_part = new_z_r;
    z->i_part = new_z_i;
}

int determine_color(int i, t_mlx *set)
{
    return rescale_window(i, range(COLOR_BLACK, COLOR_BRIGHT_RED), range(0, set->pixel_loop));
}

void render_pixel(int row, int column, t_mlx *set, int color)
{
    my_put_pixel(row, column, set->image, color);
}

static void process_pixel(int row, int column, t_mlx *set)
{
    t_com	z;
    t_com	c;
    int		i;

    i = 0;
    initialize_z_and_c(&z, &c, row, column, set);
    while (i < set->pixel_loop)
    {
        calculate_new_z(&z, &c);
        if (z.r_part * z.r_part + z.i_part * z.i_part > 4.0)
        {
            render_pixel(row, column, set, determine_color(i, set));
            return;
        }
        i++;
    }
    render_pixel(row, column, set, COLOR_BLACK);
}

void render_column(int column, t_mlx *set)
{
    int row;

    row = 0;
    while (row < W)
    {
        process_pixel(row, column, set);
        row++;
    }
}

void render_burning_ship(t_mlx *set)
{
    int column;

    column = 0;
    while (column < H)
    {
        render_column(column, set);
        column++;
    }
    mlx_put_image_to_window(set->init_c, set->window, set->image.image_ptr, 0, 0);
}
