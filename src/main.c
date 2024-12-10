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

#include "../includes/fdf.h"

static t_fdf	*fdf_init(char *windowtitle)
{
	t_fdf	*obj;
	int		fd;

	fd = open(windowtitle, O_RDONLY);
	if (fd == -1)
		ft_error("invalid file / open error");
	if (close(fd) == -1)
		ft_error("close error");
	obj = ft_calloc(1, (sizeof(t_fdf)));
	if (!obj)
		ft_error("malloc error for fdf");
	obj->mlx = mlx_init();
	obj->win = mlx_new_window(obj->mlx, WINDOWWIDTH, WINDOWHEIGHT, windowtitle);
	obj->img = mlx_new_image(obj->mlx, WINDOWWIDTH, WINDOWHEIGHT);
	obj->addr = mlx_get_data_addr(obj->img, &obj->bpp, \
									&obj->line_len, &obj->endian);
	obj->x_offset = 0;
	obj->y_offset = 0;
	obj->x_angle = -0.615472907;
	obj->y_angle = -0.523599;
	obj->z_angle = 0.615472907;
	return (obj);
}

int	main(int argc, char **argv)
{
	t_fdf	*obj;

	if (argc == 2)
	{
		obj = fdf_init(argv[1]);
		map_init(obj, argv[1]);
		ft_drawmap(obj);
		mlx_hook(obj->win, 17, 0, ft_close_win, obj);
		mlx_hook(obj->win, 2, 1L << 0, ft_keypress, obj);
		mlx_put_image_to_window(obj->mlx, obj->win, obj->img, 0, 0);
		mlx_loop(obj->mlx);
	}
	else
		ft_printf("wrong input, valid input should be: ./fdf FILENAME\n");
}
