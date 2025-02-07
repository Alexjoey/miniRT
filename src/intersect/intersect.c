/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:56:35 by amylle            #+#    #+#             */
/*   Updated: 2025/02/07 14:28:39 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <math.h>
#include <stdio.h>

void	ft_swapf(float *nptr1, float *nptr2)
{
	float	tmp;

	tmp = *nptr1;
	*nptr1 = *nptr2;
	*nptr2 = tmp;
}

bool	intersect_sphere(t_ray *ray, t_sphere *sph, float *t)
{
	t_vector	l;
	float		td[2];
	float		tca;
	float		thc;
	float		d2;

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
	if (td[0] < 1e-6)
		td[0] = td[1];
	if (td[0] < 1e-6)
		return (false);
	*t = td[0];
	return (true);
}

bool	intersect_plane(t_ray *ray, t_plane *pl, float *t)
{
	float	denominator;

	denominator = dot_product(pl->direction, ray->direction);
	if (fabs(denominator) > 1e-6)
	{
		*t = dot_product(subtract_vector(pl->pos, ray->origin), pl->direction) \
			/ denominator;
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
	if (shape->type == CYLINDER)
		return (intersect_cylinder(ray, &shape->shape.cylinder, t));
	return (false);
}
