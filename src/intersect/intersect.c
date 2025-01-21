/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:56:35 by amylle            #+#    #+#             */
/*   Updated: 2025/01/20 17:58:04 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	ft_swapf(float *nptr1, float *nptr2)
{
	float	tmp;

	tmp = *nptr1;
	*nptr1 = *nptr2;
	*nptr2 = tmp;
}

void	recalc_sphere_cache(t_vector *c_pos, t_sphere *sph)
{
	sph->l_cache = subtract_vector(sph->pos, *c_pos);
	sph->cache_valid = true;
}

//reminder to set sph->cache_valid to false whenever sph->pos or camera_pos change
bool	intersect_sphere(t_ray *ray, t_sphere *sph, float *t)
{
	t_vector	l;
	float		td[2];
	float		tca;
	float		thc;
	float		d2;

//	if (sph->cache_valid == false)
//		recalc_sphere_cache(&ray->origin, sph);
	l = subtract_vector(sph->pos, ray->origin);
	tca = dot_product(l, ray->direction);
	if (tca < 0)
		return (false);
	d2 = dot_product(l, l) - tca * tca;
	if (d2 > sph->rad_sq)
		return (false);
	thc = sqrtf(sph->rad_sq - d2);
	td[0] = tca - thc;
	td[1] = tca + thc;
	if (td[0] > td[1])
		ft_swapf(&td[0], &td[1]);
	if (td[0] < 1e-6)
		td[0] = td[1];
	if (td[0] < 1e-6)
		return (false);
	*t = td[0];
	return (true);
}

bool	intersect_circle(t_vector *c_pos, t_vector *c_dir, t_cylinder *cyl, float *t)
{
	float	denominator;

	denominator = dot_product(cyl->direction, *c_dir);
	if (denominator > 1e-6)
	{
		*t = dot_product(subtract_vector(cyl->pos, *c_pos), cyl->direction)
			/ denominator;
		return ((length_vector(subtract_vector(add_vector(*c_pos, multiply_vector(*c_dir, *t)), cyl->pos))) < cyl->diameter * 0.5);
	}
	return (false);
}
/*
bool	intersect_cylinder(t_vector *c_pos, t_vector *c_dir, t_cylinder *cyl, float *t)
{
	
}*/

void	recalc_plane_cache(t_vector *ray_origin, t_plane *pl)
{
	pl->numerator_cache = dot_product(subtract_vector(pl->pos, *ray_origin), pl->direction);
	pl->cache_valid = true;
}

bool	intersect_plane(t_ray *ray, t_plane *pl, float *t)
{
	float	denominator;

	denominator = dot_product(pl->direction, ray->direction);
	if (fabs(denominator) > 1e-6)
	{
	/*	if (pl->cache_valid == false)
			recalc_plane_cache(&ray->origin, pl);*/
		*t = dot_product(subtract_vector(pl->pos, ray->origin), pl->direction) / denominator;
		return (*t >= 0);
	}
	return (false);
}

bool	intersect(t_ray *ray, t_shape *shape, float *t)
{
	if (shape->type == SPHERE)
		return (intersect_sphere(ray, &shape->shape.sphere, t));
	if (shape->type == PLANE)
		return (intersect_plane(ray, &shape->shape.plane, t));
/*	if (shape->type == CYLINDER)
		return (intersect_cylinder(c_pos, c_dir, &shape->shape.cylinder, t));*/
	return (false);
}
