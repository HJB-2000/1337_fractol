/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:14:06 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/07 08:06:42 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

t_grid	range_b_s(int row, int column)
{
	t_grid	coord;

	coord.row = row;
	coord.column = column;
	return (coord);
}

void	initialize_z_and_c(t_com *z, t_com *c, t_grid coord, t_mlx *set)
{
	z->r_part = rescale_window(coord.row, range(-2.5, 2.5), range(0, W))
		* set->zoom_factor + set->move_row;
	z->i_part = rescale_window(coord.column, range(-2, 2), range(0, H))
		* set->zoom_factor + set->move_column;
	c->r_part = z->r_part;
	c->i_part = z->i_part;
}

void	calculate_new_z(t_com *z, t_com *c)
{
	double		zx;
	double		zy;
	double		xtemp;

	zx = fabs(z->r_part);
	zy = fabs(z->i_part);
	xtemp = zx * zx - zy * zy + c->r_part;
	zy = 2 * zx * zy + c->i_part;
	zx = xtemp;
	z->r_part = zx;
	z->i_part = zy;
}

int	determine_color(int i, t_mlx *set)
{
	int		x;
	int		color;

	x = COLOR_WHITE + COLOR_TRIPPY5;
	color = x ;
	color = (color >> 24 & 0xFF) | color ;
	color = (color >> 16 & 0xFF) | color ;
	color = (color >> 8 & 0xFF) | color ;
	return (rescale_window(i, range(COLOR_BLACK, color),
			range(0, set->pixel_loop)));
}

void	render_pixel(int row, int column, t_mlx *set, int color)
{
	my_put_pixel(row, column, set->image, color);
}
