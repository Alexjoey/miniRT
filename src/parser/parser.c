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
	while (line && line[--i] == ' ')
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

int	parse_fov(char *str, int *fov)
{
	*fov = ft_atoi(str);
	if (*fov >= 0 && *fov <= 180)
		return (true);
	return (ft_error("invalid fov given, must be in range of 0-180: ", str));
}

int	parse_ambient(t_rt *obj, char *line)
{
	char		**args;

	if (obj->ambient.initialized == true)
		return (ft_error("there can only be one ambient light", NULL));
	args = ft_split(line, ' ');
	if (ft_arrlen(args) != 3)
	{
		ft_freearray(args);
		return (ft_error("wrong amount of arguments for ambient: ", line));
	}
	if (!parse_ratio(args[1], &obj->ambient.ratio) || \
		!parse_color(args[2], &obj->ambient.color))
	{
		ft_freearray(args);
		return (false);
	}
	ft_freearray(args);
	obj->ambient.initialized = true;
	return (true);
}

//not checking if the normalised vector actually is normalised
int	parse_camera(t_rt *obj, char	*line)
{
	char		**args;

	if (obj->camera.initialized == true)
		return (ft_error("there can only be one camera light", NULL));
	args = ft_split(line, ' ');
	if (ft_arrlen(args) != 4)
	{
		ft_freearray(args);
		return (ft_error("wrong amount of arguments for camera: ", line));
	}
	if (!parse_vector(args[1], &obj->camera.pos) || \
		!parse_vector(args[2], &obj->camera.direction) || \
		!parse_fov(args[3], &obj->camera.fov))
	{
		ft_freearray(args);
		return (false);
	}
	ft_freearray(args);
	obj->camera.initialized = true;
	return (true);
}

int	parse_light(t_rt *obj, char *line)
{
	char		**args;

	if (obj->light.initialized == true)
		return (ft_error("there can only be one light", NULL));
	args = ft_split(line, ' ');
	if (ft_arrlen(args) != 4)
	{
		ft_freearray(args);
		return (ft_error("wrong amount of arguments for light: ", line));
	}
	if (!parse_vector(args[1], &obj->light.pos) || \
		!parse_ratio(args[2], &obj->light.brightness) || \
		!parse_color(args[3], &obj->light.color))
	{
		ft_freearray(args);
		return (false);
	}
	ft_freearray(args);
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

//just make an addlast function to make this shit work
int	parse_sphere(t_rt *obj, char *line)
{
	char		**args;
	t_shape		*shape;
	t_shape		*ptr;

	args = ft_split(line, ' ');
	if (ft_arrlen(args) != 4)
	{
		ft_freearray(args);
		return (ft_error("wrong amount of arguments for sphere: ", line));
	}
	shape = ft_calloc(sizeof(*shape), 1);
	if (!shape)
	{
		ft_freearray(args);
		return (ft_error("calloc error making a shape", NULL));
	}
	if (!parse_sphere_args(shape, args))
	{
		ft_freearray(args);
		return (false);
	}
	ft_freearray(args);
	if (obj->shapes == NULL)
		obj->shapes = shape;
	else
	{
		ptr = obj->shapes;
		while (ptr->next)
			ptr = ptr->next;
		ptr->next = shape;
	}
	return (true);
}

int	parse_line(t_rt *obj, char	*line)
{
	if (!ft_strncmp("A", line, 1))
		return (parse_ambient(obj, line));
	if (!ft_strncmp("C", line, 1))
		return (parse_camera(obj, line));
	if (!ft_strncmp("L", line, 1))
		return (parse_light(obj, line));
	if (!ft_strncmp("sp", line, 1))
		return (parse_sphere(obj, line));/*
	if (!ft_strncmp("pl", line, 1))
		return (parse_plane(obj, line));
	if (!ft_strncmp("cy", line, 1))
		return (parse_cylinder(obj, line));*/
	return (false);
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
			return (false);
		}
		free (line);
	}
	close(fd);
	return (true);
}
