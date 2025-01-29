/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 16:58:05 by bclaeys           #+#    #+#             */
/*   Updated: 2025/01/24 18:50:45 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static void	set_basis_vectors(t_vector *x_basis,
							t_vector *y_basis,
							t_vector *z_basis,
							t_camera cam)
{
	*x_basis = set_vector(cam.cam_matrix[0][0], cam.cam_matrix[0][1], 
					cam.cam_matrix[0][2]);
	*y_basis = set_vector(cam.cam_matrix[1][0], cam.cam_matrix[1][1], 
					cam.cam_matrix[1][2]);
	*z_basis = set_vector(cam.cam_matrix[2][0], cam.cam_matrix[2][1], 
					cam.cam_matrix[2][2]);
}

void	ft_up_rotate(void *param)
{
	static float angle;
	t_rt	*var_data;
	t_vector	x_basis;
	t_vector	y_basis;
	t_vector	z_basis;

	var_data = (t_rt*)param;
	angle += (30.0 / 180.0) * 3.14;
	var_data->camera.direction.y = cos(angle);
	var_data->camera.direction.x = sin(angle);
	normalize_vector(var_data->camera.direction);
	set_basis_vectors(&x_basis, &y_basis, &z_basis, var_data->camera);
	ft_put_new_img(var_data);
}

void	ft_down_rotate(void	*param)
{
	static float angle;
	t_rt	*var_data;
	t_vector	x_basis;
	t_vector	y_basis;
	t_vector	z_basis;

	var_data = (t_rt*)param;
	angle += (30.0 / 180.0) * 3.14;
	var_data->camera.direction.x = cos(angle);
	var_data->camera.direction.y = sin(angle);
	normalize_vector(var_data->camera.direction);
	set_basis_vectors(&x_basis, &y_basis, &z_basis, var_data->camera);
	ft_put_new_img(var_data);
}

void	ft_right_rotate(void *param)
{
	static float angle;
	t_rt	*var_data;
	t_vector	x_basis;
	t_vector	y_basis;
	t_vector	z_basis;

	var_data = (t_rt*)param;
	angle += (30.0 / 180.0) * 3.14;
	var_data->camera.direction.z = cos(angle);
	var_data->camera.direction.x = sin(angle);
	normalize_vector(var_data->camera.direction);
	set_basis_vectors(&x_basis, &y_basis, &z_basis, var_data->camera);
	ft_put_new_img(var_data);
}

void	ft_left_rotate(void	*param)
{
	static float angle;
	t_rt	*var_data;
	t_vector	x_basis;
	t_vector	y_basis;
	t_vector	z_basis;

	var_data = (t_rt*)param;
	angle += (30.0 / 180.0) * 3.14;
	var_data->camera.direction.x = cos(angle);
	var_data->camera.direction.z = sin(angle);
	normalize_vector(var_data->camera.direction);
	set_basis_vectors(&x_basis, &y_basis, &z_basis, var_data->camera);
	ft_put_new_img(var_data);
}

/* to do */
	/* 1. ervoor zorgen dat de hoek de eerste keer niet verspringt */
	/* 2. normaliseren */
	/* 3. andere hoeken */
