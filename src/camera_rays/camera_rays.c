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

bool	inter_sphere(t_vector *c_pos, t_vector *c_dir, t_shape *shape, float *t)
{
	t_vector	l;
	float		t0;
	float		t1;
	float		tca;
	float		thc;
	float		d2;

	l = subtract_vector(shape->shape.sphere.pos, *c_pos);
	tca = dot_product(l, *c_dir);
	if (tca < 0)
		return (false);
	d2 = dot_product(l, l) - tca * tca;
	if (d2 > shape->shape.sphere.rad_sq)
		return (false);
	thc = sqrtf(shape->shape.sphere.rad_sq - d2);
	t0 = tca - thc;
	t1 = tca + thc;
	if (t0 > t1)
		ft_swapf(&t0, &t1);
	if (t0 < 0.0)
		t0 = t1;
	if (t0 < 0.0)
		return (false);
	*t = t0;
	return (true);
}

bool	intersect(t_vector *c_pos, t_vector *c_dir, t_shape *shape, float *t)
{
	if (shape->type == SPHERE)
		return (inter_sphere(c_pos, c_dir, shape, t));
/*	if (shape->type == PLANE)
		return (intersect_plane());
	if (shape->type == CYLINDER)
		return (intersect_cylinder());*/
	return (false);
}

t_color	trace_ray(t_vector *camera_pos, t_vector *camera_dir, t_rt *obj)
{
//	t_color		color;
//	t_vector	p_hit;
//	t_vector	n_hit;
//	float		d;
	float		min_d;
	t_shape		*shape;
	t_shape		*ptr;
	float		t;

	ptr = obj->shapes;
	shape = NULL;
	min_d = INFINITY;
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
		return (shape->shape.sphere.color);
	return (set_color(0, 0, 0));
}

void	render(t_rt *obj)
{
	int			y;
	int			x;
	t_vector	cam_dir;
	t_color		color;

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
			my_pixel_put(&obj->mlx, x, y, convert_color(color));
			x++;
		}
		y++;
	}
}
