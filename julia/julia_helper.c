/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:04:42 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/04 08:34:59 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	my_put_pixel_julia(int row, int column, t_image image, int color)
{
	int		bytes_per_pixel;
	int		offset;

	bytes_per_pixel = image.bits_pp / 8;
	offset = (column * image.ll) + (row * bytes_per_pixel);
	*(unsigned int *)(image.addr_p + offset) = color;
}

t_grid	range_julia(int row, int column)
{
	t_grid	coord;

	coord.row = row;
	coord.column = column;
	return (coord);
}

void	init_julia_constants(t_com *c, t_mlx *set)
{
	c->r_part = set->julia_real;
	c->i_part = set->julia_imag;
}

void	map_to_complex_plane(t_com *z, t_grid coord, t_mlx *set)
{
	z->r_part = rescale_window(coord.row, range(-2, 2), range(0, W))
		* set->zoom_factor + set->move_row;
	z->i_part = rescale_window(coord.column, range(2, -2), range(0, H))
		* set->zoom_factor + set->move_column;
}

void	iterate_julia(t_com *z, t_com *c)
{
	double	z_r_squared;
	double	z_i_squared;
	double	new_z_r;
	double	new_z_i;

	z_r_squared = z->r_part * z->r_part;
	z_i_squared = z->i_part * z->i_part;
	new_z_r = z_r_squared - z_i_squared + c->r_part;
	new_z_i = 2 * z->r_part * z->i_part + c->i_part;
	z->r_part = new_z_r;
	z->i_part = new_z_i;
}
