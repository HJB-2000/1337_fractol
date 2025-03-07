/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:04:42 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/06 09:45:40 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

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
