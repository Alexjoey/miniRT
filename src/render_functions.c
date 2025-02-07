/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:12:49 by bclaeys           #+#    #+#             */
/*   Updated: 2025/02/07 14:30:10 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void	ft_put_new_img(t_rt *obj)
{
	mlx_destroy_image(obj->mlx.mlx, obj->mlx.img);
	obj->mlx.img = mlx_new_image(obj->mlx.mlx, WINDOWWIDTH, WINDOWHEIGHT);
	mlx_clear_window(obj->mlx.mlx, obj->mlx.win);
	render(obj);
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

t_vector	calc_nhit_sphere(t_vector *phit, t_sphere *sph, t_vector *ray_dir)
{
	t_vector	nhit;

	nhit = normalize_vector(subtract_vector(*phit, sph->pos));
	if (dot_product(nhit, *ray_dir) >= 1e-6)
		return (multiply_vector(nhit, -1));
	return (nhit);
}

t_vector	calc_nhit_plane(t_plane *plane, t_vector *ray_dir)
{
	if (dot_product(plane->direction, *ray_dir) >= 1e-6)
		return (multiply_vector(plane->direction, -1));
	return (plane->direction);
}

t_vector	calc_nhit_cylinder(t_vector *phit, t_cylinder *cyl, t_vector *ray_d)
{
	t_vector	phit_to_cylbase;
	t_vector	normal;
	float		base_to_phit_len;

	phit_to_cylbase = subtract_vector(*phit, cyl->base);
	base_to_phit_len = dot_product(phit_to_cylbase, cyl->direction);
	if (fabs(base_to_phit_len) <= 1e-4)
		normal = cyl->direction;
	else if (fabs(base_to_phit_len - cyl->height) <= 1e-4)
		normal = cyl->direction;
	else
		normal = normalize_vector(subtract_vector(*phit, add_vector(cyl->base,
						multiply_vector(cyl->direction, base_to_phit_len))));
	if (dot_product(normal, *ray_d) >= 1e-6)
		normal = multiply_vector(normal, -1);
	return (normal);
}
