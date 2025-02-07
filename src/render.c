/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:01:49 by amylle            #+#    #+#             */
/*   Updated: 2025/02/07 14:29:36 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "vector/vector.h"

// need to do dotproduct shit for others
t_vector	calc_nhit(t_vector *phit, t_shape *shape, t_vector *direction)
{
	if (shape->type == SPHERE)
		return (calc_nhit_sphere(phit, &shape->shape.sphere, direction));
	if (shape->type == PLANE)
		return (calc_nhit_plane(&shape->shape.plane, direction));
	if (shape->type == CYLINDER)
		return (calc_nhit_cylinder(phit, &shape->shape.cylinder, direction));
	return (set_vector(0, 0, 1));
}

t_color	get_shape_color(t_shape *shape)
{
	if (shape->type == SPHERE)
		return (shape->shape.sphere.color);
	if (shape->type == PLANE)
		return (shape->shape.plane.color);
	else
		return (shape->shape.cylinder.color);
}

int	trace_ray(t_ray *ray, t_rt *obj, t_hit *hit)
{
	t_shape		*ptr;
	float		t;

	ptr = obj->shapes;
	hit->shape = NULL;
	hit->t = INFINITY;
	while (ptr)
	{
		if (intersect(ray, ptr, &t) && t < hit->t)
		{
			hit->shape = ptr;
			hit->t = t;
		}
		ptr = ptr->next;
	}
	if (hit->shape)
	{
		hit->phit = add_vector(ray->origin, \
				multiply_vector(ray->direction, hit->t));
		hit->nhit = calc_nhit(&hit->phit, hit->shape, &ray->direction);
		hit->color = get_shape_color(hit->shape);
		return (true);
	}
	return (false);
}

int	cast_ray(t_ray *cam_ray, t_rt *obj)
{
	t_hit		hit;
	t_hit		shadow_hit;
	float		dot_prod;
	t_ray		sha_ray;
	float		tmp;

	if (trace_ray(cam_ray, obj, &hit))
	{
		sha_ray.direction = normalize_vector(\
					subtract_vector(obj->light.pos, hit.phit));
		dot_prod = dot_product(hit.nhit, sha_ray.direction);
		if (dot_prod < 0)
			return (0);
		sha_ray.origin = add_vector(hit.phit, multiply_vector(hit.nhit, 0.001));
		tmp = length_vector(subtract_vector(obj->light.pos, hit.phit));
		if (!trace_ray(&sha_ray, obj, &shadow_hit) && shadow_hit.t > tmp)
		{
			hit.color.r *= obj->light.brightness * dot_prod;
			hit.color.g *= obj->light.brightness * dot_prod;
			hit.color.b *= obj->light.brightness * dot_prod;
			return (convert_color(hit.color));
		}
	}
	return (0);
}

void	render(t_rt *obj)
{
	int		y;
	int		x;
	int		color;
	t_ray	cam_ray;

	make_cam_matrix(&obj->camera);
	cam_ray.origin = obj->camera.pos;
	y = 0;
	while (y < WINDOWHEIGHT)
	{
		x = 0;
		while (x < WINDOWWIDTH)
		{
			make_camera_ray(obj, x, y, &cam_ray.direction);
			color = cast_ray(&cam_ray, obj);
			my_pixel_put(&obj->mlx, x, y, color);
			x++;
		}
		y++;
	}
}
