/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 08:04:42 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/07 10:04:30 by jbahmida         ###   ########.fr       */
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

static	int	treat_arg(char x, int *dot_count)
{
	if (x == '.')
	{
		(*dot_count)++;
		if (*dot_count > 1)
			return (1);
	}
	else if ((x < '0' || x > '9')
		|| *dot_count > 1)
		return (1);
	return (0);
}

int	julia_checker(char **argv)
{
	int		i;
	int		j;
	int		dot;

	i = 2;
	while (argv[i])
	{
		j = 0;
		dot = 0;
		if (argv[i][j] == '+' || argv[i][j] == '-')
			j++;
		if (!argv[i][j])
			return (1);
		while (argv[i][j])
		{
			if (treat_arg(argv[i][j], &dot))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
