/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandlbrot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbahmida <jbahmida@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 23:42:02 by jbahmida          #+#    #+#             */
/*   Updated: 2025/02/19 03:53:34 by jbahmida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

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

void drawing_mandlbrot(char *title)
{  
	t_mlx   *set;

	set = _malloc(sizeof(t_mlx), NULL, false, false);
	set->title = title;
	set->esacap_check = 4;
	set->pixel_loop = 51;
	set->move_row = 0;
	set->move_column = 0;
	set->zoom_factor = 1;
	initialize_set(set);
	rendring(set);
	load_event_listeners(&set);
	mlx_loop(set->init_c);
}
