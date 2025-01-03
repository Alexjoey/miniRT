/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:16:33 by amylle            #+#    #+#             */
/*   Updated: 2024/06/11 12:43:48 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	ft_put_new_img(t_rt *obj)
{
	mlx_destroy_image(obj->mlx.mlx, obj->mlx.img);
	obj->mlx.img = mlx_new_image(obj->mlx.mlx, WINDOWWIDTH, WINDOWHEIGHT);
	mlx_clear_window(obj->mlx.mlx, obj->mlx.win);
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

int	ft_atoi_base(char *num, char *base)
{
	int	ret;
	int	i;
	int	j;
	int	baselen;

	baselen = ft_strlen(base);
	ret = 0;
	i = -1;
	while (num[++i])
	{
		j = -1;
		while (base[++j])
			if (base[j] == num[i])
				ret += ret * baselen + j;
	}
	return (ret);
}
