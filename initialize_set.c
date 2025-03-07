/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:01:22 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/06 22:37:34 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	initialize_set(t_mlx *_set)
{
	_set->init_c = mlx_init();
	if (!_set->init_c)
		_malloc(0, NULL, false, true);
	_set->window = mlx_new_window(_set->init_c, W, H, _set->title);
	if (!_set->window)
		_malloc(0, NULL, false, true);
	_set->image.image_ptr = mlx_new_image(_set->init_c, W, H);
	if (!_set->image.image_ptr)
	{
		mlx_destroy_window(_set->init_c, _set->window);
		_malloc(0, NULL, false, true);
		exit(1);
	}
	_set->image.addr_p = mlx_get_data_addr(_set->image.image_ptr,
			&_set->image.bits_pp, &_set->image.ll, &_set->image.endian);
	printf("end : %d || ll : %d \n", _set->image.endian, _set->image.ll);
	if (!_set->image.addr_p)
	{
		mlx_destroy_image(_set->init_c, _set->image.image_ptr);
		mlx_destroy_window(_set->init_c, _set->window);
		_malloc(0, NULL, false, true);
		exit(1);
	}
}

int	julia_checker(char **argv)
{
	int		i;
	int		j;
	int		dot_count;

	i = 2;
	while (argv[i])
	{
		j = 0;
		dot_count = 0;
		if (argv[i][j] == '+' || argv[i][j] == '-')
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] == '.')
				dot_count++;
			else if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			if (dot_count > 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

void	my_put_pixel(int row, int column, t_image image, int color)
{
	int	bytes_per_pixel;
	int	offset;

	bytes_per_pixel = image.bits_pp / 8;
	offset = (column * image.ll) + (row * bytes_per_pixel);
	*(unsigned int *)(image.addr_p + offset) = color;
}
