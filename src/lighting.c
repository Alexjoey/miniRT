/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:59:29 by amylle            #+#    #+#             */
/*   Updated: 2025/01/20 18:00:33 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"
#include "vector/vector.h"

t_color	get_shape_color(t_shape *shape)
{
	if (shape->type == SPHERE)
		return (shape->shape.sphere.color);
	if (shape->type == PLANE)
		return (shape->shape.plane.color);
	else
		return (shape->shape.cylinder.color);
}

t_color	calc_lighting(t_ray *ray, t_shape *shape, t_light *light, t_vector *phit, t_vector *nhit)
{
	float	intensity;
	t_color color;
	float	dotprod;
	(void) ray;

	dotprod = dot_product(*nhit, normalize_vector(subtract_vector(light->pos, *phit)));
	if (dotprod <= 0)
	{
		return ((t_color){0, 0, 0});
	}
	else
	{
		color = get_shape_color(shape);
		intensity = light->brightness * dotprod;
		if (intensity < 0)
			intensity = 0;
		color.r *= intensity;
		color.g *= intensity;
		color.b *= intensity;
		return (color);
	}
}
