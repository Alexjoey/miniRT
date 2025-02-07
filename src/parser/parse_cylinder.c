/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:40:07 by bclaeys           #+#    #+#             */
/*   Updated: 2025/02/07 14:49:11 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

//diameter and height can both be negative but should be fine?
int	parse_cylinder_args(t_cylinder *cylinder, char **args)
{
	if (!parse_vector(args[1], &cylinder->pos))
		return (false);
	if (!parse_vector(args[2], &cylinder->direction))
		return (false);
	if (length_vector(cylinder->direction) == 0)
		return (ft_error("cylinder direction vector cant have length 0", NULL));
	cylinder->direction = normalize_vector(cylinder->direction);
	cylinder->diameter = ft_atof(args[3]);
	cylinder->height = ft_atof(args[4]);
	cylinder->base = subtract_vector(cylinder->pos, \
				multiply_vector(cylinder->direction, cylinder->height * 0.5));
	cylinder->rad_sq = powf(cylinder->diameter * 0.5, 2);
	if (!parse_color(args[5], &cylinder->color))
		return (false);
	return (true);
}

int	parse_cylinder(t_rt *obj, char *line, char **args)
{
	t_shape		*shape;

	if (ft_arrlen(args) != 6)
		return (ft_error("wrong amount of arguments for cylinder: ", line));
	shape = ft_calloc(sizeof(*shape), 1);
	if (!shape)
		return (ft_error("calloc error making a shape", NULL));
	shapeadd_back(&obj->shapes, shape);
	if (!parse_cylinder_args(&shape->shape.cylinder, args))
		return (false);
	shape->type = CYLINDER;
	return (true);
}
