/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_julia.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:06:12 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/07 02:32:26 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	check_escape_and_color(t_com *z, int i, t_grid coord, t_mlx *set)
{
	double	magnitude_squared;
	int		color;
	double	v;
	double	x;

	magnitude_squared = z->r_part * z->r_part + z->i_part * z->i_part;
	if (magnitude_squared > 4.0)
	{
		v = COLOR_WHITE + COLOR_TRIPPY5;
		x = COLOR_WHITE + COLOR_TRIPPY6;
		color = rescale_window(i, range(v, x),
				range(0, set->pixel_loop));
		color = (color >> 24 & 0xFF) | color ;
		color = (color >> 16 & 0xFF) | color ;
		color = (color >> 8 & 0xFF) | color ;
		my_put_pixel(coord.row, coord.column, set->image, color);
		return (1);
	}
	return (0);
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

void	process_pixel_julia(int row, int column, t_mlx *set, t_com *c)
{
	t_com	z;
	int		i;

	i = 0;
	map_to_complex_plane(&z, range_julia(row, column), set);
	while (i < set->pixel_loop)
	{
		if (check_escape_and_color(&z, i, range_julia(row, column), set))
			return ;
		iterate_julia(&z, c);
		i++;
	}
	my_put_pixel(row, column, set->image, COLOR_WHITE);
}

void	render_julia(t_mlx *set)
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
			process_pixel_julia(row, column, set, &c);
			row++;
		}
		column++;
	}
	mlx_put_image_to_window(set->init_c, set->window,
		set->image.image_ptr, 0, 0);
}
