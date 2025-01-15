/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:41:09 by amylle            #+#    #+#             */
/*   Updated: 2025/01/15 16:26:39 by bclaeys          ###   ########.fr       */
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

/*
static void	ft_adjust_offset(int x, int y, void	*param)
{
	t_fdf	*obj;

	obj = (t_fdf *) param;
	obj->x_offset += x;
	obj->y_offset += y;
	ft_put_new_img(obj);
}

static void	ft_adjust_zoom(float offset, void *param)
{
	t_fdf	*obj;

	obj = (t_fdf *) param;
	obj->camera_zoom *= offset;
	ft_put_new_img(obj);
}

static void	ft_adjust_angle(int keycode, void *param)
{
	t_fdf	*obj;

	obj = (t_fdf *) param;
	if (keycode == 'h')
		obj->x_angle += 0.1;
	if (keycode == 'l')
		obj->x_angle += -0.1;
	if (keycode == 'j')
		obj->y_angle += 0.1;
	if (keycode == 'k')
		obj->y_angle += -0.1;
	if (keycode == 'u')
		obj->z_angle += 0.1;
	if (keycode == 'd')
		obj->z_angle += -0.1;
	ft_put_new_img(obj);
}
*/
int	ft_keypress(int keycode, void *param)
{
	if (keycode == XK_Escape)
		ft_close_win(param);/*
	if (keycode == XK_Left)
		ft_adjust_offset(-10, 0, param);
	if (keycode == XK_Right)
		ft_adjust_offset(10, 0, param);
	if (keycode == XK_Up)
		ft_adjust_offset(0, -10, param);
	if (keycode == XK_Down)
		ft_adjust_offset(0, 10, param);
	if (keycode == XK_equal)
		ft_adjust_zoom(2, param);
	if (keycode == XK_minus)
		ft_adjust_zoom(0.5, param);
	if (keycode == 'h' || keycode == 'j' || keycode == 'k'\
		|| keycode == 'l' || keycode == 'u' || keycode == 'd')
		ft_adjust_angle(keycode, param);*/
	return (0);
}
