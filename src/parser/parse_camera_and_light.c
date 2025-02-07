/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera_and_light.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:50:10 by bclaeys           #+#    #+#             */
/*   Updated: 2025/02/07 14:51:49 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	parse_fov(char *str, float *scale)
{
	int	fov;

	fov = ft_atoi(str);
	if (fov >= 0 && fov <= 180)
	{
		*scale = tanf(fov * 0.5 * M_PI / 180);
		return (true);
	}
	return (ft_error("invalid fov given, must be in range of 0-180: ", str));
}

int	parse_ambient(t_rt *obj, char *line, char **args)
{
	if (obj->ambient.initialized == true)
		return (ft_error("there can only be one ambient light", NULL));
	if (ft_arrlen(args) != 3)
		return (ft_error("wrong amount of arguments for ambient: ", line));
	if (!parse_ratio(args[1], &obj->ambient.ratio) || \
		!parse_color(args[2], &obj->ambient.color))
		return (false);
	obj->ambient.initialized = true;
	return (true);
}

//not checking if the normalised vector actually is normalised
int	parse_camera(t_rt *obj, char *line, char **args)
{
	if (obj->camera.initialized == true)
		return (ft_error("there can only be one camera light", NULL));
	if (ft_arrlen(args) != 4)
		return (ft_error("wrong amount of arguments for camera: ", line));
	if (!parse_vector(args[1], &obj->camera.pos) || \
		!parse_vector(args[2], &obj->camera.direction) || \
		!parse_fov(args[3], &obj->camera.scale))
		return (false);
	if (length_vector(obj->camera.direction) == 0)
		return (ft_error("camera direction vector cant have length 0", NULL));
	obj->camera.direction = normalize_vector(obj->camera.direction);
	obj->camera.ratio = WINDOWWIDTH / (float) WINDOWHEIGHT;
	obj->camera.initialized = true;
	return (true);
}

int	parse_light(t_rt *obj, char *line, char **args)
{
	if (obj->light.initialized == true)
		return (ft_error("there can only be one light", NULL));
	if (ft_arrlen(args) != 4)
		return (ft_error("wrong amount of arguments for light: ", line));
	if (!parse_vector(args[1], &obj->light.pos) || \
		!parse_ratio(args[2], &obj->light.brightness) || \
		!parse_color(args[3], &obj->light.color))
		return (false);
	obj->light.initialized = true;
	return (true);
}
