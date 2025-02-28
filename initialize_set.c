/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:01:22 by jbahmida          #+#    #+#             */
/*   Updated: 2025/02/28 10:06:04 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void initialize_set(t_mlx *_set)
{
    _set->init_c = _malloc(0, mlx_init(), false, false);
    if (!_set->init_c)
        _malloc(0, NULL, false, true);
    _set->window = _malloc(0, mlx_new_window(_set->init_c, W, H, _set->title), false, false);
    if (!_set->window)
        _malloc(0, NULL, false, true);
    _set->image.image_ptr = _malloc(0, mlx_new_image(_set->init_c, W, H), false, false);
    if (!_set->image.image_ptr)
    {   
        mlx_destroy_window(_set->init_c, _set->window);
        _malloc(0, NULL, false, true);
    }
    _set->image.addr_p = _malloc(0, mlx_get_data_addr(_set->image.image_ptr, &_set->image.bits_pp,
                                                        &_set->image.ll, &_set->image.endian), false, false);                                
}