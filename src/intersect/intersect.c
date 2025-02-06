/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:56:35 by amylle            #+#    #+#             */
/*   Updated: 2025/02/06 13:12:08 by bclaeys          ###   ########.fr       */
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

// same here, save rad^2
// also jesus christ can we just use the other /
bool	intersect_circle(t_ray *ray, t_cylinder *cyl, t_vector cylpos, float *t)
{
	float	denominator;

	denominator = dot_product(cyl->direction, ray->direction);
	if (fabs(denominator) > 1e-6)
	{
		*t = dot_product(subtract_vector(cylpos, ray->origin), cyl->direction)
			/ denominator;
		return ((length_vector_squared(subtract_vector(add_vector(ray->origin, \
				multiply_vector(ray->direction, *t)), cylpos))) < cyl->rad_sq);
	}
	return (false);
}

//need to at least save rad^2
static double	find_discriminant(t_cylinder *cyl,
								t_vector cylax_ray_perp,
								float *tdarray0,
								float *tdarray1)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = length_vector_squared(cylax_ray_perp);
	b = dot_product(cylax_ray_perp, cyl->origin_perp_to_cylbase) * 2.0;
	c = length_vector_squared(cyl->origin_perp_to_cylbase) - cyl->rad_sq;
	discriminant = pow(b, 2) - 4 * a * c;
	*tdarray0 = (-b - sqrt(discriminant)) / (2 * a);
	*tdarray1 = (-b + sqrt(discriminant)) / (2 * a);
	return (discriminant);
}

//is this swapf actully needed
static bool	calc_hitpoint_sides(float *check_caps,
								float *td,
								t_cylinder *cyl,
								t_ray *ray)
{
	t_vector	cylax_ray_perp;
	float		tdarray[2];
	double		discriminant;

	cyl->origin_to_cylbase = subtract_vector(ray->origin, cyl->base);
	cyl->origin_perp_to_cylbase = subtract_vector(cyl->origin_to_cylbase,
			multiply_vector(cyl->direction, dot_product(cyl->origin_to_cylbase,
					cyl->direction)));
	cylax_ray_perp = subtract_vector(ray->direction, multiply_vector(\
				cyl->direction, dot_product(ray->direction, cyl->direction)));
	discriminant = find_discriminant(cyl, cylax_ray_perp,
			&tdarray[0], &tdarray[1]);
	if (discriminant < -1e-6)
		return (false);
	if (tdarray[0] < 1e-6)
		tdarray[0] = tdarray[1];
	if (tdarray[0] < -1e-6 && tdarray[1] < -1e-6)
		return (false);
	if (tdarray[0] > tdarray[1])
		ft_swapf(&tdarray[0], &tdarray[1]);
	*td = tdarray[0];
	*check_caps = dot_product(add_vector(cyl->origin_to_cylbase, \
					multiply_vector(ray->direction, *td)), cyl->direction);
	return (true);
}

bool	intersect_cylinder(t_ray *ray, t_cylinder *cyl, float *t)
{
	float		td;
	float		cap_t;
	float		cap_t2;
	float		check_caps;
	bool		td_valid;

	cap_t2 = 0;
	cap_t = 0;
	*t = INFINITY;
	td_valid = false;
	if (!calc_hitpoint_sides(&check_caps, &td, cyl, ray))
		return (*t = -1, false);
	if ((td > 1e-6 && check_caps > 1e-6 && check_caps < cyl->height + 1e-6))
	{
		td_valid = true;
		*t = td;
	}
	if (intersect_circle(ray, cyl, cyl->base, &cap_t) && cap_t < *t)
		*t = cap_t;
	if (intersect_circle(ray, cyl, add_vector(cyl->base,
				multiply_vector(cyl->direction, cyl->height)),
			&cap_t2) && cap_t2 < *t)
		*t = cap_t2;
	return (td_valid == true || cap_t > 0 || cap_t2 > 0);
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
