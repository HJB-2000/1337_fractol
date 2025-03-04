/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_math.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 20:27:56 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/04 07:57:03 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

void	my_put_pixel(int row, int column, t_image image, int color)
{
	int	bytes_per_pixel;
	int	offset;

	bytes_per_pixel = image.bits_pp / 8;
	offset = (column * image.ll) + (row * bytes_per_pixel);
	*(unsigned int *)(image.addr_p + offset) = color;
}

double	rescale_window(double unscaled_num, t_range new, t_range old)
{
	return ((new.max - new.min) * (unscaled_num - old.min)
		/ (old.max - old.min) + new.min);
}

t_range	range(double min_range, double max_range)
{
	t_range	range;

	range.max = max_range;
	range.min = min_range;
	return (range);
}

t_com	calculate_new_com(t_com num, t_com point)
{
	t_com	res;
	t_com	tmp;

	tmp.r_part = (num.r_part * num.r_part) - (num.i_part * num.i_part);
	tmp.i_part = 2 * num.r_part * num.i_part;
	res.r_part = tmp.r_part + point.r_part;
	res.i_part = tmp.i_part + point.i_part;
	return (res);
}
