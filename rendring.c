#include "fractol.h"


void my_put_pixel(int row, int colomn, t_image image, int color)
{
    int offset;

    offset = (colomn * image.ll) + (row * (image.bits_pp / 8));
    *(unsigned int *)(image.addr_p + offset) = color;
}


void treat_pixel(int row, int column, t_mlx *set)
{  
    t_com   num;
    t_com   set_point;
    int     i;
    int     color;

    num.r_part = 0;
    num.i_part = 0;
    set_point.r_part = rescale_window(row, -2, +2, 0, W);
    set_point.i_part = rescale_window(column, +2, -2, 0, H);
    i = 0;
    while (i < set->pixel_loop)
    {
        num = calculate_new_com(num, set_point);
        if ((num.r_part * num.r_part) + (num.i_part * num.i_part) > set->esacap_check)
        {
            color = rescale_window(i, COLOR_WHITE, COLOR_BLACK, 0, set->pixel_loop);
            my_put_pixel(row, column, set->image, color);
            return ;
        }
        i++;
    }
    my_put_pixel(row, column, set->image, COLOR_TRIPPY6);

}
void rendring(t_mlx *set)
{
    // row ===> width
    // column ===> height
    int row;
    int column = 0;

    while (column < H)
    {   
        row = 0;
        while (row < W)
        {
            treat_pixel(row, column, set);
            row++;
        }
        column++;
    }
    mlx_put_image_to_window(set->init_c, set->window, set->image.image_ptr, 0, 0);
}
