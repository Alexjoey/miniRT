/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:12:49 by bclaeys           #+#    #+#             */
/*   Updated: 2025/01/15 16:26:37 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	ft_put_new_img(t_rt *obj)
{
	mlx_destroy_image(obj->mlx.mlx, obj->mlx.img);
	obj->mlx.img = mlx_new_image(obj->mlx.mlx, WINDOWWIDTH, WINDOWHEIGHT);
	mlx_clear_window(obj->mlx.mlx, obj->mlx.win);
	//rerender here
	mlx_put_image_to_window(obj->mlx.mlx, obj->mlx.win, obj->mlx.img, 0, 0);
}

void	my_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WINDOWWIDTH || y < 0 || y > WINDOWHEIGHT)
		return ;
	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}
