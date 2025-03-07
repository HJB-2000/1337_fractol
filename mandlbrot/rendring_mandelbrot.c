/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_mandelbrot.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:42:22 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/07 08:12:18 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	calculate_iterations(t_com num, t_com set_point, t_mlx *set)
{
	int		i;

	i = 0;
	while (i < set->pixel_loop)
	{
		num = calculate_new_com(num, set_point);
		if ((num.r_part * num.r_part) + (num.i_part * num.i_part)
			> set->esacap_check)
			return (i);
		i++;
	}
	return (i);
}

void	treat_pixel(int row, int column, t_mlx *set, t_resc dimention)
{
	t_com	num;
	t_com	p;
	int		iterations;
	int		color;

	num.r_part = 0;
	num.i_part = 0;
	p.r_part = dimention.resc_row[row] * set->zoom_factor + set->move_row;
	p.i_part = dimention.resc_column[column] * set->zoom_factor
		+ set->move_column;
	iterations = calculate_iterations(num, p, set);
	if (iterations < set->pixel_loop)
	{
		color = rescale_window(iterations,
				range(COLOR_BLACK, COLOR_BRIGHT_YELLOW),
				range(0, set->pixel_loop));
		color = (color >> 24 & 0xFF) | color ;
		color = (color >> 16 & 0xFF) | color ;
		color = (color >> 8 & 0xFF) | color ;
	}
	else
		color = COLOR_BLACK;
	my_put_pixel(row, column, set->image, color);
}

t_resc	grid(void)
{
	t_resc	d;
	size_t	row_size;
	size_t	column_size;
	int		r;
	int		c;

	row_size = (W * sizeof(double));
	column_size = (H * sizeof(double));
	d.resc_row = _malloc(row_size, NULL, false, false);
	d.resc_column = _malloc(column_size, NULL, false, false);
	r = 0;
	c = 0;
	while (r < W)
	{
		d.resc_row[r] = rescale_window(r, range(-2, 2), range(0, W));
		r++;
	}
	while (c < H)
	{
		d.resc_column[c] = rescale_window(c, range(2, -2), range(0, H));
		c++;
	}
	return (d);
}

void	rendring_mandelbrot(t_mlx *set)
{
	t_resc	dimention;
	int		row;
	int		column;

	dimention = grid();
	row = 0;
	while (row < W)
	{
		column = 0;
		while (column < H)
		{
			treat_pixel(row, column, set, dimention);
			column++;
		}
		row++;
	}
	mlx_put_image_to_window(set->init_c, set->window,
		set->image.image_ptr, 0, 0);
}
