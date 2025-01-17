/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:15:56 by amylle            #+#    #+#             */
/*   Updated: 2025/01/15 16:16:16 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"
#include <limits.h>

//make this to rotate the initial camera direction with
void	make_cam_matrix(t_camera *camera)
{
	t_vector	forward;
	t_vector	right;
	t_vector	up;

	up = set_vector(0, 1, 0);
	forward = normalize_vector(camera->direction);
	right = cross_product(up, forward);
	up = cross_product(forward, right);
	camera->cam_matrix[0][0] = right.x;
	camera->cam_matrix[0][1] = right.y;
	camera->cam_matrix[0][2] = right.z;
	camera->cam_matrix[1][0] = up.x;
	camera->cam_matrix[1][1] = up.y;
	camera->cam_matrix[1][2] = up.z;
	camera->cam_matrix[2][0] = forward.x;
	camera->cam_matrix[2][1] = forward.y;
	camera->cam_matrix[2][2] = forward.z;
	camera->cam_matrix[3][3] = 1;
}

t_vector	multiply_vector_matrix(t_vector vector, float m[4][4])
{
	t_vector	ret;

	ret.x = vector.x * m[0][0] + vector.y * m[1][0] + vector.z * m[2][0];
	ret.y = vector.x * m[0][1] + vector.y * m[1][1] + vector.z * m[2][1];
	ret.z = vector.x * m[0][2] + vector.y * m[1][2] + vector.z * m[2][2];
	return (ret);
}

//have make_cam_matrix be somewhere better
void	make_camera_ray(t_rt *obj, int x, int y, t_vector *cam_dir)
{
	t_camera	*cam;

	cam = &obj->camera;
	cam_dir->x = (2 * ((x + 0.5) / WINDOWWIDTH) - 1) * cam->scale * cam->ratio;
	cam_dir->y = (1 - 2 * ((y + 0.5) / WINDOWHEIGHT)) * cam->scale;
	cam_dir->z = 1.0;
	*cam_dir = multiply_vector_matrix(*cam_dir, cam->cam_matrix);
	*cam_dir = normalize_vector(*cam_dir);
}

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
bool	intersect_sphere(t_vector *c_pos, 
							t_vector *c_dir, 
							t_sphere *sph, 
							float *t)
{
	t_vector	l;
	float		td[2];
	float		tca;
	float		thc;
	float		d2;

	if (sph->cache_valid == false)
		recalc_sphere_cache(c_pos, sph);
	l = sph->l_cache;
	tca = dot_product(l, *c_dir);
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
	if (td[0] < 0)
		td[0] = td[1];
	if (td[0] < 0)
		return (false);
	*t = td[0];
	return (true);
}

void	recalc_plane_cache(t_vector *c_pos, t_plane *pl)
{
	pl->numerator_cache = dot_product(subtract_vector(pl->pos, *c_pos), pl->direction);
	pl->cache_valid = true;
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

bool	intersect_cylinder(t_vector *c_pos, t_vector *c_dir, t_cylinder *cyl, float *t)
{
	
}

//can maybe cache pl->pos and c_pos subtraction result
bool	intersect_plane(t_vector *c_pos, t_vector *c_dir, t_plane *pl, float *t)
{
	float	denominator;

	denominator = dot_product(pl->direction, *c_dir);
	if (denominator > 1e-6)
	{
		if (pl->cache_valid == false)
			recalc_plane_cache(c_pos, pl);
		*t = pl->numerator_cache / denominator;

		return (*t >= 0);
	}
	return (false);
}

bool	intersect(t_vector *c_pos, t_vector *c_dir, t_shape *shape, float *t)
{
	if (shape->type == SPHERE)
		return (intersect_sphere(c_pos, c_dir, &shape->shape.sphere, t));
	if (shape->type == PLANE)
		return (intersect_plane(c_pos, c_dir, &shape->shape.plane, t));
	if (shape->type == CYLINDER)
		return (intersect_cylinder(c_pos, c_dir, &shape->shape.cylinder, t));
	return (false);
}

int	trace_ray(t_vector *camera_pos, t_vector *camera_dir, t_rt *obj)
{
	float		min_d;
	t_shape		*shape;
	t_shape		*ptr;
	float		t;
	float		percent;
//	t_color		color;
//	t_vector	p_hit;
//	t_vector	n_hit;
//	float		d;

	ptr = obj->shapes;
	shape = NULL;
	min_d = INFINITY;
	t = 0;
	while (ptr)
	{
		if (intersect(camera_pos, camera_dir, ptr, &t) && t < min_d)
		{
			shape = ptr;
			min_d = t;
		}
		ptr = ptr->next;
	}
	
	if (shape)
	{
		percent = min_d * 0.003;
		if (percent > 1.0)
			percent = 1.0;
		if (percent < 0.2)
			percent = 0.2;
		if (shape->type == SPHERE)
			return (interpol_color(convert_color(shape->shape.sphere.color), 0, percent));
		if (shape->type == PLANE)
			return (interpol_color(convert_color(shape->shape.plane.color), 0, percent));
		if (shape->type == CYLINDER)
			return (interpol_color(convert_color(shape->shape.cylinder.color), 0, percent));
	}
	return (0);
}

#include <time.h>

void	render(t_rt *obj)
{
	int			y;
	int			x;
	t_vector	cam_dir;
	int			color;

    clock_t start, end;
    double cpu_time_used;
	start = clock();

	make_cam_matrix(&obj->camera);
	cam_dir = set_vector(0.0, 0.0, 0.0);
	y = 0;
	while (y < WINDOWHEIGHT)
	{
		x = 0;
		while (x < WINDOWWIDTH)
		{
			make_camera_ray(obj, x, y, &cam_dir);
			color = trace_ray(&obj->camera.pos, &cam_dir, obj);
			my_pixel_put(&obj->mlx, x, y, color);
			x++;
		}
		y++;
	}
	end = clock();
	cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by function: %f seconds\n", cpu_time_used);
}
