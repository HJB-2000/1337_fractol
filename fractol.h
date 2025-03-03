#ifndef FRACTOL_H
#define FRACTOL_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

#include <signal.h>

#include "minilibx_opengl_20191021/mlx.h"

#define FIXED_SCALE (1 << 16) // 2^16 scaling factor

// Standard colors in 0xRRGGBB format
#define COLOR_BLACK    0x000000
#define COLOR_RED      0xFF0000
#define COLOR_GREEN    0x00FF00
#define COLOR_YELLOW   0xFFFF00
#define COLOR_BLUE     0x0000FF
#define COLOR_MAGENTA  0xFF00FF
#define COLOR_CYAN     0x00FFFF
#define COLOR_WHITE    0xFFFFFF

// Bright variants
#define COLOR_BRIGHT_BLACK   0x808080
#define COLOR_BRIGHT_RED     0xFF6666
#define COLOR_BRIGHT_GREEN   0x66FF66
#define COLOR_BRIGHT_YELLOW  0xFFFF66
#define COLOR_BRIGHT_BLUE    0x6666FF
#define COLOR_BRIGHT_MAGENTA 0xFF66FF
#define COLOR_BRIGHT_CYAN    0x66FFFF
#define COLOR_BRIGHT_WHITE   0xF8F8FF

// Psychedelic colors
#define COLOR_TRIPPY1  0xFF1493  // Deep Pink
#define COLOR_TRIPPY2  0x4B0082  // Indigo
#define COLOR_TRIPPY3  0x00FF7F  // Spring Green
#define COLOR_TRIPPY4  0xFFA500  // Orange
#define COLOR_TRIPPY5  0x00BFFF  // Deep Sky Blue
#define COLOR_TRIPPY6  0x9400D3  // Dark Violet
#define COLOR_TRIPPY7  0xFF4500  // Red-Orange
#define COLOR_TRIPPY8  0xADFF2F  // Green-Yellow


# define H 700
# define W 700


typedef struct s_range
{
    double  min;
    double  max;
}   t_range;

typedef struct s_rescale
{
    double *resc_row;
    double *resc_column;
}   t_resc;

typedef struct s_garbage
{
    void *_malloc;
    int index;
    struct s_garbage *next;
} t_garbage;

typedef struct s_image
{
    void *image_ptr;	/*mlx_new_image*/
    char *addr_p;		/*mlx_get_data_addr()*/
    int bits_pp;     /*bits per pixel*/
    int ll;         /*line_lenght*/
    int endian;		/*i dont know*/
}   t_image;

typedef struct s_mlx_d
{
    void    *init_c; /*mlx_init()*/
    void    *window; /*mlx_new_window*/
    char    *title;
    int     esacap_check;
    int     pixel_loop;
    double     move_row;
    double     move_column;
    double      zoom_factor;
    double  julia_real;
    double  julia_imag;
    double time;
    int     flag;
	t_image image; /*struct contain the info about image*/

}t_mlx ;

typedef struct s_number
{
    double r_part;
    double i_part;
}   t_com;


void drawing_mandlbrot(char *title);
void initialize_set(t_mlx *set);


t_com calculate_new_com(t_com num, t_com point);


/*rendreing*/

void my_put_pixel(int row, int colomn, t_image image, int color);
void	treat_pixel(int row, int column, t_mlx *set, t_resc dimention);
void rendring(t_mlx *set);
/******************************/
 /*z_math*/
 t_com calculate_new_com(t_com num, t_com point);
// double rescale_window(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
/******************************/
void load_event_listeners(t_mlx **set);

/*helper_function*/
int	ft_strncmp(const char *s1, const char *s2, size_t n);
void    my_putstr(char *str);
void add_node(t_garbage **head, t_garbage *new_node);
void *_malloc(size_t size, void *ptr, bool free_flag, bool error_flag);

/*to be change*/
/*********************/


void initialize_set_julia(t_mlx *_set);
void drawing_julia(char *title, double v1, double v2);
void render_julia(t_mlx *set);
void my_put_pixel_julia(int row, int column, t_image image, int color);
void load_event_listeners_julia(t_mlx **set);
double ft_atoi(const char *str);

void drawing_burning_ship(char *title);
void initialize_burning_ship(t_mlx *_set);
void render_burning_ship(t_mlx *set);
void load_event_listeners_burnig_ship(t_mlx **set);
int handle_destroy_b(t_mlx **set);
int handle_mouse_enter_b(int b, int x, int y, t_mlx **set);
int handle_keypress_b(int keycode, t_mlx **set);
void render_ship(t_mlx *set);
int animate(t_mlx *set);
void initialize_set(t_mlx *_set);
double	rescale_window(double unscaled_num, t_range new, t_range old);
t_range	range(double min_range,  double max_range);
void l();
#endif