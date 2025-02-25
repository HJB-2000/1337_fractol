#include "../fractol.h"
void render_burning_ship(t_mlx *set)
{
    int row, column;
    t_com z, c;
    int i, color;

    for (column = 0; column < H; column++)
    {
        for (row = 0; row < W; row++)
        {
            z.r_part = rescale_window(row, -2, 2, 0, W) * set->zoom_factor + set->move_row;
            z.i_part = rescale_window(column, 2, -2, 0, H) * set->zoom_factor + set->move_column;

            c.r_part = z.r_part;
            c.i_part = z.i_part;

            i = 0;
            while (i < set->pixel_loop)
            {
                double z_r_abs = fabs(z.r_part);
                double z_i_abs = fabs(z.i_part);
                double new_z_r = z_r_abs * z_r_abs - z_i_abs * z_i_abs + c.r_part;
                double new_z_i = 2 * z_r_abs * z_i_abs + c.i_part;
                z.r_part = new_z_r;
                z.i_part = new_z_i;
                if (z.r_part * z.r_part + z.i_part * z.i_part > 4.0)
                {
                    color = rescale_window(i, COLOR_BLACK, COLOR_BRIGHT_RED, 0, set->pixel_loop);
                    my_put_pixel(row, column, set->image, color);
                    break;
                }

                i++;
            }
            if (i == set->pixel_loop)
            {
                my_put_pixel(row, column, set->image, COLOR_BLACK);
            }
        }
    }
    mlx_put_image_to_window(set->init_c, set->window, set->image.image_ptr, 0, 0);
}


void render_ship(t_mlx *set)
{
    int row;
    int column;
    t_com z;
    t_com c;
    int color;
    int i;

    column = 0;
    while (column < H)
    {
        row = 0;
        while (row < W)
        {
            z.r_part = rescale_window(row, -2, 2, 0, W) * set->zoom_factor + set->move_row;
            z.i_part = rescale_window(column, 2, -2, 0, H) * set->zoom_factor + set->move_column;
            c.r_part = z.r_part;
            c.i_part = z.i_part;
            i = 0;
            while (i < set->pixel_loop)
            {
                double z_r_abs = fabs(z.r_part);
                double z_i_abs = fabs(z.i_part);
                double new_z_r = z_r_abs * z_r_abs - z_i_abs * z_i_abs + c.r_part;
                double new_z_i = 2 * z_r_abs * z_i_abs + c.i_part;
                z.r_part = new_z_r;
                z.i_part = new_z_i;
                if (z.r_part * z.r_part + z.i_part * z.i_part > 4.0)
                {
                    double t = i * 0.05 + set->time;
                    int red = (sin(t) + 1) * 127.5;
                    int green = (sin(t + 2) + 1) * 127.5;
                    int blue = (sin(t + 4) + 1) * 127.5;
                    color = (red << 16) | (green << 8) | blue;
                    my_put_pixel(row, column, set->image, color);
                    break;
                }
                i++;
            }
            if (i == set->pixel_loop)
            {
                double t = set->time; // Use time for background color
                int trippy_color = (int)(127.5 * (sin(t) + 1)) << 16 |
                                  (int)(127.5 * (sin(t + 2) + 1)) << 8 |
                                  (int)(127.5 * (sin(t + 4) + 1));
                my_put_pixel(row, column, set->image, trippy_color);
            }
            row++;
        }
        column++;
    }
}