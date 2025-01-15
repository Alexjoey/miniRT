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

void	make_cam_matrix(t_camera *camera)
{
	t_vector forward;
	t_vector right;
	t_vector up;

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
}

t_vector	multiply_vector_matrix(t_vector vector, float m[4][4])
{
	t_vector	ret;
	float		w;

	ret.x = vector.x * m[0][0] + vector.y * m[1][0] + vector.z * m[2][0] + m[3][0];
    ret.y = vector.x * m[0][1] + vector.y * m[1][1] + vector.z * m[2][1] + m[3][1];
    ret.z = vector.x * m[0][2] + vector.y * m[1][2] + vector.z * m[2][2] + m[3][2];
    w = vector.x * m[0][3] + vector.y * m[1][3] + vector.z * m[2][3] + m[3][3];
	if (w != 1)
	{
		ret.x /= w;
		ret.y /= w;
		ret.z /= w;
	}
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
	make_cam_matrix(cam);
	*cam_dir = multiply_vector_matrix(*cam_dir, cam->cam_matrix);
}

t_color	trace_ray(t_vector *camera_pos, t_vector *camera_dir, t_rt *obj)
{
	t_color color;

	return (color);
}
void	render(t_rt *obj)
{
	int			y;
	int			x;
	t_vector	cam_dir;
	t_color		color;

	make_cam_matrix(&obj->camera);
	y = 0;
	while (y < WINDOWHEIGHT)
	{
		x = 0;
		while (x < WINDOWWIDTH)
		{
			make_camera_ray(obj, x, y, &cam_dir);
			color = trace_ray(&obj->camera.pos, &cam_dir, obj);
			my_pixel_put(&obj->mlx, x, y, convert_color(color));

		}
		y++;
	}
}
