/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 16:15:56 by amylle            #+#    #+#             */
/*   Updated: 2025/01/20 18:02:50 by amylle           ###   ########.fr       */
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
void	make_camera_ray(t_rt *obj, int x, int y, t_vector *cam_ray_dir)
{
	t_camera	*c;

	c = &obj->camera;
	cam_ray_dir->x = (2 * ((x + 0.5) / WINDOWWIDTH) - 1) * c->scale * c->ratio;
	cam_ray_dir->y = (1 - 2 * ((y + 0.5) / WINDOWHEIGHT)) * c->scale;
	cam_ray_dir->z = 1.0;
	*cam_ray_dir = multiply_vector_matrix(*cam_ray_dir, c->cam_matrix);
	*cam_ray_dir = normalize_vector(*cam_ray_dir);
}
