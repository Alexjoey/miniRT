/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:33:04 by bclaeys           #+#    #+#             */
/*   Updated: 2025/02/07 14:52:56 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

//diameter can be smaller than 0 rn, idk if i care
int	parse_sphere_args(t_shape *shape, char **args)
{
	if (!parse_vector(args[1], &shape->shape.sphere.pos))
		return (false);
	shape->shape.sphere.diameter = ft_atof(args[2]);
	if (!parse_color(args[3], &shape->shape.sphere.color))
		return (false);
	return (true);
}

void	shapeadd_back(t_shape	**root, t_shape *shape)
{
	t_shape	*ptr;

	if (!*root)
	{
		*root = shape;
		return ;
	}
	else
	{
		ptr = *root;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = shape;
	}
}

//just make an addlast function to make this shit work
int	parse_sphere(t_rt *obj, char *line, char **args)
{
	t_shape		*shape;

	if (ft_arrlen(args) != 4)
		return (ft_error("wrong amount of arguments for sphere: ", line));
	shape = ft_calloc(sizeof(*shape), 1);
	if (!shape)
		return (ft_error("calloc error making a shape", NULL));
	shapeadd_back(&obj->shapes, shape);
	if (!parse_sphere_args(shape, args))
		return (false);
	shape->shape.sphere.rad_sq = powf(shape->shape.sphere.diameter * 0.5, 2);
	shape->type = SPHERE;
	shape->shape.sphere.cache_valid = false;
	return (true);
}

int	parse_plane_args(t_shape *shape, char **args)
{
	if (!parse_vector(args[1], &shape->shape.plane.pos))
		return (false);
	if (!parse_vector(args[2], &shape->shape.plane.direction))
		return (false);
	if (length_vector(shape->shape.plane.direction) == 0)
		return (ft_error("plane direction vector cant have length 0", NULL));
	shape->shape.plane.direction = \
		normalize_vector(shape->shape.plane.direction);
	if (!parse_color(args[3], &shape->shape.plane.color))
		return (false);
	return (true);
}

int	parse_plane(t_rt *obj, char *line, char **args)
{
	t_shape		*shape;

	if (ft_arrlen(args) != 4)
		return (ft_error("wrong amount of arguments for plane: ", line));
	shape = ft_calloc(sizeof(*shape), 1);
	if (!shape)
		return (ft_error("calloc error making a shape", NULL));
	shapeadd_back(&obj->shapes, shape);
	if (!parse_plane_args(shape, args))
		return (false);
	shape->type = PLANE;
	shape->shape.plane.cache_valid = false;
	return (true);
}
