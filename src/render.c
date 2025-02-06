/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:01:49 by amylle            #+#    #+#             */
/*   Updated: 2025/02/06 13:12:09 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "vector/vector.h"

t_vector	calc_nhit_sphere(t_vector *phit, t_sphere *sphere)
{
/*	if (length_vector_squared(subtract_vector(*phit, sphere->pos)) < sphere->rad_sq)
		return (multiply_vector(normalize_vector(subtract_vector(*phit, sphere->pos)), -1.0));*/
	return (normalize_vector(subtract_vector(*phit, sphere->pos)));
}

t_vector	calc_nhit_plane(t_light *light, t_plane *plane, t_vector *phit)
{
	if (dot_product(plane->direction, normalize_vector(subtract_vector(light->pos, *phit))) < 0)
		return (multiply_vector(plane->direction, -1.0));
	return (plane->direction);
}


t_vector	calc_nhit_cylinder(t_vector *phit, t_cylinder *cyl, t_vector *ray_dir)
{
	t_vector	phit_to_cylbase;
	t_vector	normal;
	float	base_to_phit_len;

	phit_to_cylbase = subtract_vector(*phit, cyl->base);
	base_to_phit_len = dot_product(phit_to_cylbase, cyl->direction);
	if (fabs(base_to_phit_len) <= 1e-6)
		normal = normalize_vector(multiply_vector(cyl->direction, -1));
	else if (fabs(base_to_phit_len - cyl->height) <= 1e-6)
		normal = cyl->direction;
	else
		normal = normalize_vector(subtract_vector(*phit, add_vector(cyl->base, 
						multiply_vector(cyl->direction, base_to_phit_len))));
	if (dot_product(normal, *ray_dir) <= 1e-6)
		multiply_vector(normal, -1);
	return (normal);	
}

t_vector	calc_nhit(t_light *light, t_vector *phit, t_shape *shape, t_vector *direction)
{
	if (shape->type == SPHERE)
		return (calc_nhit_sphere(phit, &shape->shape.sphere));
	if (shape->type == PLANE)
		return (calc_nhit_plane(light, &shape->shape.plane, phit));
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
		hit->phit = add_vector(ray->origin, multiply_vector(ray->direction, hit->t));
		hit->nhit = calc_nhit(&obj->light, &hit->phit, hit->shape, &ray->direction);
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
	t_ray		shadow_ray;
	float		tmp;

	if (trace_ray(cam_ray, obj, &hit))
	{
		shadow_ray.direction = normalize_vector(subtract_vector(obj->light.pos, hit.phit));
		dot_prod = dot_product(hit.nhit, shadow_ray.direction);
		if (dot_prod < 0)
			return (0);
		shadow_ray.origin = add_vector(hit.phit, multiply_vector(hit.nhit, 0.01));
		tmp = length_vector(subtract_vector(obj->light.pos, hit.phit));
		if (!trace_ray(&shadow_ray, obj, &shadow_hit) && shadow_hit.t > tmp)
		{
			hit.color.r *= obj->light.brightness * dot_prod;
			hit.color.g *= obj->light.brightness * dot_prod;
			hit.color.b *= obj->light.brightness * dot_prod;
			return (convert_color(hit.color));
		}
	}
	return (0);
}

#include <time.h>

void	render(t_rt *obj)
{
	int		y;
	int		x;
	int		color;
	t_ray	cam_ray;
    clock_t	start; 
	clock_t	end;
    double	cpu_time_used;

	start = clock();
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
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
	printf("Time taken by function: %f seconds\n", cpu_time_used);
}
