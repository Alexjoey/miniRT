/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 18:01:49 by amylle            #+#    #+#             */
/*   Updated: 2025/01/20 18:01:49 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "vector/vector.h"

t_vector	calc_nhit_sphere(t_vector *phit, t_sphere *sphere)
{
	return (normalize_vector(subtract_vector(*phit, sphere->pos)));
}

t_vector	calc_nhit_plane(t_light *light, t_plane *plane, t_vector *phit)
{
	if (dot_product(plane->direction, normalize_vector(subtract_vector(light->pos, *phit))) < 0)
		return (multiply_vector(plane->direction, -1.0));
	return (plane->direction);
}

t_vector	calc_nhit(t_light *light, t_vector *phit, t_shape *shape)
{
	if (shape->type == SPHERE)
		return (calc_nhit_sphere(phit, &shape->shape.sphere));
	if (shape->type == PLANE)
		return (calc_nhit_plane(light, &shape->shape.plane, phit));
	/*if (shape->type == SPHERE)
		return (calc_nhit_sphere(phit, shape));*/
	return (set_vector(0, 0, 1));
}

int	trace_ray(t_ray *cam_ray, t_rt *obj)
{
	float		min_d;
	t_shape		*shape;
	t_shape		*ptr;
	float		t;
	t_color		color;
	t_vector	phit;
	t_vector	nhit;

	ptr = obj->shapes;
	shape = NULL;
	min_d = INFINITY;
	t = 0;
	while (ptr)
	{
		if (intersect(cam_ray, ptr, &t) && t < min_d)
		{
			shape = ptr;
			min_d = t;
		}
		ptr = ptr->next;
	}
	if (shape)
	{
		phit = add_vector(cam_ray->origin, multiply_vector(cam_ray->direction, min_d));
		nhit = calc_nhit(&obj->light, &phit, shape);
		color = calc_lighting(cam_ray, shape, &obj->light, &phit, &nhit);
		return (convert_color(color));
	}
	return (rgb_to_int(0, 0, 200));
}

#include <time.h>

void	render(t_rt *obj)
{
	int			y;
	int			x;
	int			color;
	t_ray		cam_ray;

    clock_t start, end;
    double cpu_time_used;
	start = clock();

	make_cam_matrix(&obj->camera);
	cam_ray.origin = obj->camera.pos;
	cam_ray.direction = set_vector(0.0, 0.0, 0.0);
	y = 0;
	while (y < WINDOWHEIGHT)
	{
		x = 0;
		while (x < WINDOWWIDTH)
		{
			make_camera_ray(obj, x, y, &cam_ray.direction);
			color = trace_ray(&cam_ray, obj);
			my_pixel_put(&obj->mlx, x, y, color);
			x++;
		}
		y++;
	}
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by function: %f seconds\n", cpu_time_used);
}
