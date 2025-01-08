/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 17:13:28 by amylle            #+#    #+#             */
/*   Updated: 2025/01/08 17:19:58 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	parse_file(t_rt	*obj, char *filename)
{
	int		fd;
	int		ret;
	char	*line;

	(void)obj;
	if (ft_strncmp(".rt", filename + ft_strlen(filename) - 3, 3))
		return (ft_error("not a .rt file: ", filename));
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (ft_error("file not found: ", filename));
	ret = true;
	while (ret == true)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line = remove_whitespace(line);
	}
	return (true);
}
