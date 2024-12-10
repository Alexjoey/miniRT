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

#include "../includes/fdf.h"

void	ft_put_new_img(t_fdf *obj)
{
	mlx_destroy_image(obj->mlx, obj->img);
	obj->img = mlx_new_image(obj->mlx, WINDOWWIDTH, WINDOWHEIGHT);
	mlx_clear_window(obj->mlx, obj->win);
	mlx_put_image_to_window(obj->mlx, obj->win, obj->img, 0, 0);
	ft_drawmap(obj);
}

void	my_pixel_put(t_fdf *obj, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x > WINDOWWIDTH || y < 0 || y > WINDOWHEIGHT)
		return ;
	dst = obj->addr + (y * obj->line_len + x * (obj->bpp / 8));
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
