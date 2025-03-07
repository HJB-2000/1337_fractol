/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship_events.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:53:16 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/06 19:46:27 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	handle_keypress_b(int keycode, t_mlx **set)
{
	if (keycode == 53)
	{
		my_putstr("ESC key pressed. Closing window...\n");
		mlx_destroy_image((*set)->init_c, (*set)->image.image_ptr);
		mlx_destroy_window((*set)->init_c, (*set)->window);
		_malloc(0, NULL, true, false);
		atexit(l);
		exit(0);
	}
	if (keycode == 69)
		(*set)->pixel_loop += 50;
	if (keycode == 78)
		(*set)->pixel_loop -= 50;
	if (keycode == 123)
		(*set)->move_row += 0.5;
	if (keycode == 124)
		(*set)->move_row -= 0.5;
	if (keycode == 125)
		(*set)->move_column -= 0.5;
	if (keycode == 126)
		(*set)->move_column += 0.5;
	render_burning_ship(*set);
	return (0);
}

int	handle_mouse_enter_b(int b, int x, int y, t_mlx **set)
{
	double	mouse_x_fractal;
	double	mouse_y_fractal;

	if (!set || !*set)
		return (0);
	mouse_x_fractal = rescale_window(x, range(-2.5, 2.5), range(0, W))
		* (*set)->zoom_factor + (*set)->move_row;
	mouse_y_fractal = rescale_window(y, range(-2, 2), range(0, H))
		* (*set)->zoom_factor + (*set)->move_column;
	if (b == 5)
		(*set)->zoom_factor *= 0.95;
	else if (b == 4)
		(*set)->zoom_factor *= 1.05;
	(*set)->move_row = mouse_x_fractal - rescale_window(x, range(-2.5, 2.5),
			range(0, W)) * (*set)->zoom_factor;
	(*set)->move_column = mouse_y_fractal - rescale_window(y, range(-2, 2),
			range(0, H)) * (*set)->zoom_factor;
	mlx_loop_hook((*set)->init_c, animate, *set);
	return (0);
}

int	handle_destroy_b(t_mlx **set)
{
	my_putstr("Window closed.\n");
	mlx_destroy_image((*set)->init_c, (*set)->image.image_ptr);
	mlx_destroy_window((*set)->init_c, (*set)->window);
	_malloc(0, NULL, true, false);
	atexit(l);
	exit(0);
}

void	load_event_listeners_burnig_ship(t_mlx **set)
{
	mlx_hook((*set)->window, 2, 0, handle_keypress_b, set);
	mlx_hook((*set)->window, 17, 0, handle_destroy_b, set);
	mlx_mouse_hook((*set)->window, handle_mouse_enter_b, set);
}
