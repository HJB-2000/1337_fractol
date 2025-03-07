/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 19:34:34 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/07 09:05:36 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <limits.h>
# include <signal.h>
# include "minilibx_opengl_20191021/mlx.h"

// # define FIXED_SCALE (1 << 16)
// Standard colors in 0xRRGGBB format
# define COLOR_BLACK    0x000000
# define COLOR_RED      0xFF0000
# define COLOR_GREEN    0x00FF00
# define COLOR_YELLOW   0xFFFF00
# define COLOR_BLUE     0x0000FF
# define COLOR_MAGENTA  0xFF00FF
# define COLOR_CYAN     0x00FFFF
# define COLOR_WHITE    0xFFFFFF
// Bright variants
# define COLOR_BRIGHT_BLACK   0x808080
# define COLOR_BRIGHT_RED     0xFF6666
# define COLOR_BRIGHT_GREEN   0x66FF66
# define COLOR_BRIGHT_YELLOW  0xFFFF66
# define COLOR_BRIGHT_BLUE    0x6666FF
# define COLOR_BRIGHT_MAGENTA 0xFF66FF
# define COLOR_BRIGHT_CYAN    0x66FFFF
# define COLOR_BRIGHT_WHITE   0xF8F8FF
// Psychedelic colors
# define COLOR_TRIPPY1  0xFF1493  // Deep Pink
# define COLOR_TRIPPY2  0x4B0082  // Indigo
# define COLOR_TRIPPY3  0x00FF7F  // Spring Green
# define COLOR_TRIPPY4  0xFFA500  // Orange
# define COLOR_TRIPPY5  0x00BFFF  // Deep Sky Blue
# define COLOR_TRIPPY6  0x9400D3  // Dark Violet
# define COLOR_TRIPPY7  0xFF4500  // Red-Orange
# define COLOR_TRIPPY8  0xADFF2F  // Green-Yellow

# define H 700
# define W 700

typedef struct s_grid
{
	int	row;
	int	column;
}	t_grid;

typedef struct s_range
{
	double	min;
	double	max;
}	t_range;

typedef struct s_rescale
{
	double	*resc_row;
	double	*resc_column;
}	t_resc;

typedef struct s_garbage
{
	void				*_malloc;
	int					index;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_image
{
	void	*image_ptr;
	char	*addr_p;
	int		bits_pp;
	int		ll;
	int		endian;
}	t_image;

typedef struct s_mlx_d
{
	void	*init_c;
	void	*window;
	char	*title;
	int		esacap_check;
	int		pixel_loop;
	double	move_row;
	double	move_column;
	double	zoom_factor;
	double	julia_real;
	double	julia_imag;
	double	time;
	int		flag;
	t_image	image;

}	t_mlx;

typedef struct s_number
{
	double	r_part;
	double	i_part;
}	t_com;

/*Mandelbrot*/
void	rendring_mandelbrot(t_mlx *set);
t_resc	grid(void);
void	treat_pixel(int row, int column, t_mlx *set, t_resc dimention);
int		calculate_iterations(t_com num, t_com set_point, t_mlx *set);
/*helper_func*/
void	my_put_pixel(int row, int column, t_image image, int color);
double	rescale_window(double unscaled_num, t_range new, t_range old);
t_range	range(double min_range, double max_range);
t_com	calculate_new_com(t_com num, t_com point);

/*julia*/
void	render_julia(t_mlx *set);
void	process_pixel_julia(int row, int column, t_mlx *set, t_com *c);
int		check_escape_and_color(t_com *z, int i, t_grid coord, t_mlx *set);
/*julia_helper*/
t_grid	range_julia(int row, int column);
int		check_escape_and_color(t_com *z, int i, t_grid coord, t_mlx *set);
void	map_to_complex_plane(t_com *z, t_grid coord, t_mlx *set);
void	iterate_julia(t_com *z, t_com *c);
void	init_julia_constants(t_com *c, t_mlx *set);
/*mandelbrot && julia events*/
void	load_event_listeners(t_mlx **set);
int		handle_destroy(t_mlx **set);
int		handle_mouse_enter(int b, int x, int y, t_mlx **set);
int		handle_keypress_1(int keycode, t_mlx **set);
/*burning_ship*/
void	render_burning_ship(t_mlx *set);
void	render_column(int column, t_mlx *set);
void	process_pixel_b_s(t_grid coord, t_mlx *set);
int		animate(t_mlx *set);
/*burning_ship_helper*/
void	render_pixel(int row, int column, t_mlx *set, int color);
t_grid	range_b_s(int row, int column);
int		determine_color(int i, t_mlx *set);
void	calculate_new_z(t_com *z, t_com *c);
void	initialize_z_and_c(t_com *z, t_com *c, t_grid coord, t_mlx *set);
/*burning_ship_events*/
void	load_event_listeners_burnig_ship(t_mlx **set);
int		handle_destroy_b(t_mlx **set);
int		handle_mouse_enter_b(int b, int x, int y, t_mlx **set);
int		handle_keypress_b(int keycode, t_mlx **set);
/*initialize_set*/
void	initialize_set(t_mlx *_set);
int		julia_checker(char **argv);
/*my_malloc*/
void	*_malloc(size_t size, void *ptr, bool free_flag, bool error_flag);
void	*treat_ptr(size_t size, void *ptr);
void	_free(t_garbage **list);
void	add_node(t_garbage **head, t_garbage *new_node);

/*helper fuctions*/
double	ft_atoi(const char *str);
void	my_putstr(char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

#endif