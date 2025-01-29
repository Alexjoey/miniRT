/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:41:09 by amylle            #+#    #+#             */
/*   Updated: 2025/01/24 18:36:34 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "vector/vector.h"
#include <X11/keysym.h>

#define ZOOM_IN 0.5
#define ZOOM_OUT 1.5

int	ft_close_win(void *param)
{
	t_rt	*obj;

	obj = (t_rt *) param;
	mlx_destroy_window(obj->mlx.mlx, obj->mlx.win);
	mlx_destroy_image(obj->mlx.mlx, obj->mlx.img);
	mlx_destroy_display(obj->mlx.mlx);
	free (obj->mlx.mlx);
	free_shapes(obj->shapes);
	exit (0);
}


int	ft_keypress(int keycode, void *param)
{
	if (keycode == XK_Escape)
		ft_close_win(param);
	if (keycode == XK_Up) 
		ft_rotate_x_axis(param, 10.0/180.0 * M_PI);
	if (keycode == XK_Right)
		ft_rotate_y_axis(param, 10.0/180.0 * M_PI);
	if (keycode == XK_Down) 
		ft_rotate_x_axis(param, -10.0/180.0 * M_PI);
	if (keycode == XK_Left)
		ft_rotate_y_axis(param, -10.0/180.0 * M_PI);
	if (keycode == XK_equal)
		ft_adjust_zoom(param, ZOOM_IN);
	if (keycode == XK_minus)
		ft_adjust_zoom(param, ZOOM_OUT);
	/* if (keycode == 'h' || keycode == 'j' || keycode == 'k'\ */
	/* 	|| keycode == 'l' || keycode == 'u' || keycode == 'd') */
	/* 	ft_adjust_angle(keycode, param); */
	return (0);
}
