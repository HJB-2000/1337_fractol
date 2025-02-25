#include "../fractol.h"

void my_put_pixel_julia(int row, int column, t_image image, int color)
{
    int bytes_per_pixel = image.bits_pp / 8;
    int offset = (column * image.ll) + (row * bytes_per_pixel);
    *(unsigned int *)(image.addr_p + offset) = color;
}

// void render_julia(t_mlx *set)
// {
//     int row, column;
//     t_com z, c;
//     int i, color;

//     c.r_part = set->julia_real;
//     c.i_part = set->julia_imag;
//     for (column = 0; column < H; column++)
//     {
//         for (row = 0; row < W; row++)
//         {
//             z.r_part = rescale_window(row, -2, 2, 0, W) * set->zoom_factor + set->move_row;
//             z.i_part = rescale_window(column, 2, -2, 0, H) * set->zoom_factor + set->move_column;

//             i = 0;
//             while (i < set->pixel_loop)
//             {
//                 double z_r_squared = z.r_part * z.r_part;
//                 double z_i_squared = z.i_part * z.i_part;

//                 if (z_r_squared + z_i_squared > 4.0)
//                 {
//                     color = rescale_window(i, COLOR_BLACK, COLOR_BRIGHT_RED, 0, set->pixel_loop);
//                     my_put_pixel(row, column, set->image, color);
//                     break;
//                 }
//                 double new_z_r = z_r_squared - z_i_squared + c.r_part;
//                 double new_z_i = 2 * z.r_part * z.i_part + c.i_part;
//                 z.r_part = new_z_r;
//                 z.i_part = new_z_i;

//                 i++;
//             }
//             if (i == set->pixel_loop)
//             {
//                 my_put_pixel_julia(row, column, set->image, COLOR_BLACK);
//             }
//         }
//     }
//     mlx_put_image_to_window(set->init_c, set->window, set->image.image_ptr, 0, 0);
// }


void render_julia(t_mlx *set)
{
    int row;
    int column;
    int i;
    int color;
    t_com z;
    t_com c;
    double z_r_squared;
    double z_i_squared;
    double new_z_r;
    double new_z_i;


    c.r_part = set->julia_real;
    c.i_part = set->julia_imag;
    
    column = 0;
    while (column < H)
    {   
        row = 0;
        while (row < W)
        {
            z.r_part = rescale_window(row, -2, 2, 0, W) * set->zoom_factor + set->move_row;
            z.i_part = rescale_window(column, 2, -2, 0, H) * set->zoom_factor + set->move_column;
            i = 0;
            while (i < set->pixel_loop)
            {
                z_r_squared = z.r_part * z.r_part;
                z_i_squared = z.i_part * z.i_part;
                if (z_r_squared + z_i_squared > 4.0)
                {
                    color = rescale_window(i, COLOR_BLACK, COLOR_BRIGHT_RED, 0, set->pixel_loop);
                    my_put_pixel(row, column, set->image, color);
                    break;
                }
                new_z_r = z_r_squared - z_i_squared + c.r_part;
                new_z_i = 2 * z.r_part * z.i_part + c.i_part;
                z.r_part = new_z_r;
                z.i_part = new_z_i;
                i++;
            }
            if (i == set->pixel_loop)
            {
                my_put_pixel_julia(row, column, set->image, COLOR_BLACK);
            }
            row++;
        }
        column++;
    }
    mlx_put_image_to_window(set->init_c, set->window, set->image.image_ptr, 0, 0);
}

