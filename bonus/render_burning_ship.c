/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_burning_ship.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:46:42 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/04 10:56:59 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	process_pixel_b_s(t_grid coord, t_mlx *set)
{
	t_com	z;
	t_com	c;
	int		i;

	i = 0;
	initialize_z_and_c(&z, &c, range_b_s(coord.row, coord.column), set);
	while (i < set->pixel_loop)
	{
		calculate_new_z(&z, &c);
		if (z.r_part * z.r_part + z.i_part * z.i_part > 4.0)
		{
			render_pixel(coord.row, coord.column, set, determine_color(i, set));
			return ;
		}
		i++;
	}
	render_pixel(coord.row, coord.column, set, COLOR_BLACK);
}

void	render_column(int column, t_mlx *set)
{
	int		row;

	row = 0;
	while (row < W)
	{
		process_pixel_b_s(range_b_s(row, column), set);
		row++;
	}
}

void	render_burning_ship(t_mlx *set)
{
	int		column;

	column = 0;
	while (column < H)
	{
		render_column(column, set);
		column++;
	}
	mlx_put_image_to_window(set->init_c, set->window,
		set->image.image_ptr, 0, 0);
}
