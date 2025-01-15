/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:41:21 by amylle            #+#    #+#             */
/*   Updated: 2025/01/15 16:27:34 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include <unistd.h>

static void	minirt_init(t_rt *var_data, char *windowtitle)
{
	var_data->mlx.mlx = mlx_init();
	var_data->mlx.win = mlx_new_window(var_data->mlx.mlx, WINDOWWIDTH, WINDOWHEIGHT,
									windowtitle);
	var_data->mlx.img = mlx_new_image(var_data->mlx.mlx, WINDOWWIDTH, WINDOWHEIGHT);
	var_data->mlx.addr = mlx_get_data_addr(var_data->mlx.img, &var_data->mlx.bpp,
									&var_data->mlx.line_len, &var_data->mlx.endian);
}

int	test_render(t_rt *var_data)
{
	int				x;
	int				y;
	t_shape			*tmp;

	x = 0;
	y = 0;
	tmp = var_data->shapes;
	while (tmp)
	{
		while (y <= WINDOWHEIGHT)
		{
			while (x <= WINDOWWIDTH)	
			{
				if (tmp->type ==SPHERE)
					if ((tmp->shape.sphere.diameter / 2) 
								< sqrt((x - tmp->shape.sphere.pos.x) 
								* (x - tmp->shape.sphere.pos.x) 
								+ (y - tmp->shape.sphere.pos.x) 
								* (y - tmp->shape.sphere.pos.x)))
						my_pixel_put(&var_data->mlx, x, y, 
								convert_color(tmp->shape.sphere.color));
				/* else if (tmp->type == PLANE) */
				/* else if (tmp->type == CYLINDER) */
				x++;			
			}
			x = 0;
			y += 10;
		}
		tmp = tmp->next;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_rt	var_data;

	if (argc != 2)
	{
		ft_error("wrong input, valid input should be: ./miniRT scene\n", NULL);
		return (1);
	}
	ft_bzero(&var_data, sizeof(var_data));
	if (!parse_file(&var_data, argv[1]))
		return (2);
	minirt_init(&var_data, argv[1]);
	mlx_hook(var_data.mlx.win, 17, 0, ft_close_win, &var_data);
	mlx_hook(var_data.mlx.win, 2, 1L << 0, ft_keypress, &var_data);
	mlx_put_image_to_window(var_data.mlx.mlx, var_data.mlx.win, 
			var_data.mlx.img, 0, 0);
	test_render(&var_data);
	mlx_loop(var_data.mlx.mlx);
}
