/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 12:43:31 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/07 09:06:14 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static	void	common_events(int keycode, t_mlx **set)
{
	if (keycode == 69)
		(*set)->pixel_loop += 10;
	if (keycode == 78)
		(*set)->pixel_loop -= 10;
	if (keycode == 123)
		(*set)->move_row += 0.5;
	if (keycode == 124)
		(*set)->move_row -= 0.5;
	if (keycode == 125)
		(*set)->move_column += 0.5;
	if (keycode == 126)
		(*set)->move_column -= 0.5;
	return ;
}

int	handle_keypress_1(int keycode, t_mlx **set)
{
	if (keycode == 53)
	{
		my_putstr("ESC key pressed. Closing window...\n");
		mlx_destroy_image((*set)->init_c, (*set)->image.image_ptr);
		mlx_destroy_window((*set)->init_c, (*set)->window);
		_malloc(0, NULL, true, false);
		exit(0);
	}
	common_events(keycode, set);
	if ((*set)->flag == 2)
	{
		if (keycode == 0)
			(*set)->julia_real -= 0.01;
		else if (keycode == 2)
			(*set)->julia_real += 0.01;
		else if (keycode == 13)
			(*set)->julia_imag += 0.01;
		else if (keycode == 1)
			(*set)->julia_imag -= 0.01;
		render_julia(*set);
		return (0);
	}
	rendring_mandelbrot(*set);
	return (0);
}

int	handle_mouse_enter(int b, int x, int y, t_mlx **set)
{
	double	mouse_x_fractal;
	double	mouse_y_fractal;

	mouse_x_fractal = rescale_window(x, range(-2, 2), range(0, W))
		* (*set)->zoom_factor + (*set)->move_row;
	mouse_y_fractal = rescale_window(y, range(2, -2), range(0, H))
		* (*set)->zoom_factor + (*set)->move_column;
	if (b == 5)
		(*set)->zoom_factor *= 0.95;
	else if (b == 4)
		(*set)->zoom_factor *= 1.05;
	(*set)->move_row = mouse_x_fractal - rescale_window(x, range(-2, 2),
			range(0, W)) * (*set)->zoom_factor;
	(*set)->move_column = mouse_y_fractal - rescale_window(y, range(2, -2),
			range(0, H)) * (*set)->zoom_factor;
	if ((*set)->flag == 2)
	{
		render_julia(*set);
		return (0);
	}
	rendring_mandelbrot(*set);
	return (0);
}

int	handle_destroy(t_mlx **set)
{
	my_putstr("Window closed.\n");
	mlx_destroy_image((*set)->init_c, (*set)->image.image_ptr);
	mlx_destroy_window((*set)->init_c, (*set)->window);
	_malloc(0, NULL, true, false);
	exit(0);
}

void	load_event_listeners(t_mlx **set)
{
	mlx_hook((*set)->window, 2, 0, handle_keypress_1, set);
	mlx_hook((*set)->window, 17, 0, handle_destroy, set);
	mlx_mouse_hook((*set)->window, handle_mouse_enter, set);
}
