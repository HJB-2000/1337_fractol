#include "fractol.h"

double rescale_window(double unscaled_num, double new_min, double new_max, double old_min, double old_max)
{
    return ((new_max - new_min) * (unscaled_num - old_min) / (old_max - old_min) + new_min ) ;
}

t_com calculate_new_com(t_com num, t_com point)
{
    t_com res;
    t_com tmp;

    tmp.r_part = (num.r_part * num.r_part) - (num.i_part * num.i_part);
    tmp.i_part = 2 * num.r_part * num.i_part;

    res.r_part = tmp.r_part + point.r_part;
    res.i_part = tmp.i_part + point.i_part;
    return (res);
}