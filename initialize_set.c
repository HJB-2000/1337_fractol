/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:01:22 by jbahmida          #+#    #+#             */
/*   Updated: 2025/03/01 12:37:15 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void initialize_set(t_mlx *_set)
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
    _set->image.addr_p = mlx_get_data_addr(_set->image.image_ptr, &_set->image.bits_pp,
                                                        &_set->image.ll, &_set->image.endian);
    if (!_set->image.addr_p)
    {
        mlx_destroy_image(_set->init_c, _set->image.image_ptr);   
        mlx_destroy_window(_set->init_c, _set->window);
        _malloc(0, NULL, false, true);
        exit(1);
    }
}
