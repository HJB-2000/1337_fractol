/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:29:23 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/07 02:29:18 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	l(void)
{
	system("leaks fractol");
}

int	animate(t_mlx *set)
{
	set->time += 1;
	if (set->pixel_loop == 70)
		set->pixel_loop = 50;
	if (set->time == 10)
	{
		set->pixel_loop += 1;
		set->time = 0.0;
	}
	render_burning_ship(set);
	return (0);
}

t_mlx	*create_set(t_mlx	*set, char **argv, int flag)
{
	double		v1;
	double		v2;
	char		*title;

	v1 = 0.0;
	v2 = 0.0;
	set = _malloc(sizeof(t_mlx), NULL, false, false);
	title = argv[1];
	if (flag == 2)
	{
		v1 = ft_atoi(argv[2]);
		v2 = ft_atoi(argv[3]);
	}
	set->flag = flag;
	set->title = title;
	set->esacap_check = 4;
	set->pixel_loop = 50;
	set->move_row = 0;
	set->move_column = 0;
	set->zoom_factor = 1;
	set->julia_real = v1;
	set->julia_imag = v2;
	set->time = 0.00;
	return (set);
}

void	draw(int flag, char **argv)
{
	t_mlx	*set;

	set = NULL;
	set = create_set(set, argv, flag);
	initialize_set(set);
	printf("%d \n", set->image.ll);
	if (flag == 1)
	{
		rendring_mandelbrot(set);
	}
	else if (flag == 2)
	{
		render_julia(set);
	}
	else if (flag == 3)
	{
		load_event_listeners_burnig_ship(&set);
		mlx_loop_hook(set->init_c, animate, set);
		mlx_loop(set->init_c);
	}
	load_event_listeners(&set);
	mlx_loop(set->init_c);
}

void	treat_args(int argc, char **argv)
{
	int	drawing_flag;

	drawing_flag = 0;
	if (!ft_strncmp(argv[1], "Mandelbrot", 11))
		drawing_flag = 1;
	else if (!ft_strncmp(argv[1], "Julia", 6))
	{
		if (argc != 4 || julia_checker(argv))
		{
			my_putstr("Error: incorrect parameters.\n");
			my_putstr("Error: Julia set requires two additional arguments.\n");
			my_putstr("for more convient rendring -2 < args < 2\n");
			return ;
		}
		drawing_flag = 2;
	}
	else if (!ft_strncmp(argv[1], "burning_ship", 13))
		drawing_flag = 3;
	if (drawing_flag != 0)
	{
		draw(drawing_flag, argv);
		return ;
	}
	return ;
}

int	main(int argc, char **argv)
{
	if (argc < 2 || !argv[1])
	{
		my_putstr("Error: Missing fractal type argument.\n");
		return (1);
	}
	if (argc == 2 || argc == 4)
	{
		treat_args(argc, argv);
	}
	my_putstr("please enter a valide arguments exmples:\n\
	./fractol Mandelbrot\n\t./fractol Julia <value 1><value 2>\n\
	./fractol burning_ship\n");
	atexit(l);
	return (0);
}
