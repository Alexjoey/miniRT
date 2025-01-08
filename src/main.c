/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:41:21 by amylle            #+#    #+#             */
/*   Updated: 2024/06/05 13:41:24 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static void	minirt_init(t_rt *obj, char *windowtitle)
{
	int		fd;

	fd = open(windowtitle, O_RDONLY);
	ft_bzero(obj, sizeof(*obj));
	obj->mlx.mlx = mlx_init();
	obj->mlx.win = mlx_new_window(obj->mlx.mlx, WINDOWWIDTH, WINDOWHEIGHT, \
							   windowtitle);
	obj->mlx.img = mlx_new_image(obj->mlx.mlx, WINDOWWIDTH, WINDOWHEIGHT);
	obj->mlx.addr = mlx_get_data_addr(obj->mlx.img, &obj->mlx.bpp, \
									&obj->mlx.line_len, &obj->mlx.endian);
}

int	main(int argc, char **argv)
{
	t_rt	obj;

	if (argc != 2)
	{
		ft_printf("wrong input, valid input should be: ./miniRT scene\n");
		return (1);
	}
	if (!parse_file(&obj, argv[1]))
		return (-1);
	minirt_init(&obj, argv[1]);
	mlx_hook(obj.mlx.win, 17, 0, ft_close_win, &obj);
	mlx_hook(obj.mlx.win, 2, 1L << 0, ft_keypress, &obj);
	mlx_put_image_to_window(obj.mlx.mlx, obj.mlx.win, obj.mlx.img, 0, 0);
	mlx_loop(obj.mlx.mlx);
}
