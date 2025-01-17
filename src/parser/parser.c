/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:13:28 by amylle            #+#    #+#             */
/*   Updated: 2025/01/10 18:19:28 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//could maybe add some checking to check if theyre giving in valid int/floats
//need to test for only newlines maybe
#include "../../inc/minirt.h"

//removes tabs and ending whitespace
char	*remove_whitespace(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == '\t' || line[i] == '\n')
			line[i] = ' ';
		i++;
	}
	while (line && line[i] && line[--i] == ' ')
		line[i] = 0;
	return (line);
}

int	parse_ratio(char *str, float	*ra)
{
	float	ratio;

	ratio = ft_atof(str);
	if (ratio < 0.0 || ratio > 1.0)
		return (ft_error("invalid ambient ratio in: ", str));
	else
		*ra = ratio;
	return (true);
}

int	is_valid_color(const t_color *col)
{
	if (col->r >= 0 && col->r <= 255 && col->g >= 0 && \
		col->g <= 255 && col->b >= 0 && col->b <= 255)
		return (true);
	return (false);
}

int	parse_color(char *str, t_color *col)
{
	char	**split;

	split = ft_split(str, ',');
	if (ft_arrlen(split) != 3)
	{
		ft_freearray(split);
		return (ft_error("wrong amount of color arguments in: ", str));
	}
	col->r = ft_atoi(split[0]);
	col->g = ft_atoi(split[1]);
	col->b = ft_atoi(split[2]);
	ft_freearray(split);
	if (!is_valid_color(col))
		return (ft_error("invalid color values in: ", str));
	return (true);
}

int	parse_vector(char *str, t_vector *vec)
{
	char	**split;

	split = ft_split(str, ',');
	if (ft_arrlen(split) != 3)
	{
		ft_freearray(split);
		return (ft_error("wrong amount of vector arguments in: ", str));
	}
	vec->x = ft_atof(split[0]);
	vec->y = ft_atof(split[1]);
	vec->z = ft_atof(split[2]);
	ft_freearray(split);
	return (true);
}

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

//diameter and height can both be negative but should be fine?
int	parse_cylinder_args(t_shape *shape, char **args)
{
	if (!parse_vector(args[1], &shape->shape.cylinder.pos))
		return (false);
	if (!parse_vector(args[2], &shape->shape.cylinder.direction))
		return (false);
	shape->shape.cylinder.diameter = ft_atof(args[3]);
	shape->shape.cylinder.height = ft_atof(args[4]);
	if (!parse_color(args[5], &shape->shape.cylinder.color))
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
	if (!parse_cylinder_args(shape, args))
		return (false);
	shape->type = CYLINDER;
	return (true);
}

int	parse_line(t_rt *obj, char	*line)
{
	int		ret;
	char	**args;

	if (!line || !line[0] || (line[0] == ' ' && line[1] == '\0'))
		return (true);
	args = ft_split(line, ' ');
	if (!ft_strncmp("A", args[0], 2))  
		ret = parse_ambient(obj, line, args);
	else if (!ft_strncmp("C", args[0], 2))
		ret = parse_camera(obj, line, args);
	else if (!ft_strncmp("L", args[0], 2))
		ret = parse_light(obj, line, args);
	else if (!ft_strncmp("sp", args[0], 3))
		ret = parse_sphere(obj, line, args);
	else if (!ft_strncmp("pl", args[0], 3))
		ret = parse_plane(obj, line, args);
	else if (!ft_strncmp("cy", args[0], 3))
		ret = parse_cylinder(obj, line, args);
	else
		ret = ft_error("invalid input: ", line);
	ft_freearray(args);
	return (ret);
}

int	parse_file(t_rt	*obj, char *filename)
{
	int		fd;
	char	*line;

	if (ft_strncmp(".rt", filename + ft_strlen(filename) - 3, 3))
		return (ft_error("not a .rt file: ", filename));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_error("file not found: ", filename));
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = remove_whitespace(line);
		if (!parse_line(obj, line))
		{
			free (line);
			close (fd);
			free_shapes(obj->shapes);
			return (false);
		}
		free (line);
	}
	close(fd);
	return (true);
}
