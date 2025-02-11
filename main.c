#include "minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include <string.h>

typedef struct s_win {
    int height;
    int width;
} t_win;

typedef struct s_data {
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
} t_data;

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    memcpy(dst, &color, sizeof(unsigned int));  
}

int main()
{
    t_win size;
    t_data img;

    size.height = 1080;
    size.width = 1920;

    void *ptr = mlx_init();
    if (!ptr) {
        printf("Error: mlx_init() failed\n");
        return 1;
    }

    void *win = mlx_new_window(ptr, size.width, size.height, "new");
    if (!win) {
        printf("Error: mlx_new_window() failed\n");
        return 1;
    }

    img.img = mlx_new_image(ptr, size.width, size.height);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    my_mlx_pixel_put(&img, 5, 5, 0x00FF0F00);    
    mlx_put_image_to_window(ptr, win, img.img, 0, 0);
    mlx_loop(ptr);  // Corrected

    return 0;
}
