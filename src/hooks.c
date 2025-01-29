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
#include <X11/keysym.h>

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

static void	ft_rotate_x_axis(void *param, double angle)
	if (keycode == XK_Left) 
		ft_rotate_x_axis(param, 10);
	/* if (keycode == XK_Right) */
	/* 	ft_adjust_offset(10, 0, param); */
	/* if (keycode == XK_Up) */
	/* 	ft_adjust_offset(0, -10, param); */
	/* if (keycode == XK_Down) */
	/* 	ft_adjust_offset(0, 10, param); */

	// if (keycode == XK_Left)
	// 	ft_left_rotate(param);
	// if (keycode == XK_Right)
	// 	ft_right_rotate(param);
	// if (keycode == XK_Up)
	// 	ft_up_rotate(param);
	// if (keycode == XK_Down)
	// 	ft_down_rotate(param);
	/* if (keycode == XK_equal) */
	/* 	ft_adjust_zoom(2, param); */
	/* if (keycode == XK_minus) */
	/* 	ft_adjust_zoom(0.5, param); */
	/* if (keycode == 'h' || keycode == 'j' || keycode == 'k'\ */
	/* 	|| keycode == 'l' || keycode == 'u' || keycode == 'd') */
	/* 	ft_adjust_angle(keycode, param); */
	return (0);
}
