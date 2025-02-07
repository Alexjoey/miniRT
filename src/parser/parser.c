/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:13:28 by amylle            #+#    #+#             */
/*   Updated: 2025/02/07 14:52:43 by bclaeys          ###   ########.fr       */
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

int	parse_ratio(char *str, float *ra)
{
	float	ratio;

	ratio = ft_atof(str);
	if (ratio < 0.0 || ratio > 1.0)
		return (ft_error("invalid ambient ratio in: ", str));
	else
		*ra = ratio;
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

//need to add a check at the end for if theres no light/no camera/no ambient
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
