/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 14:52:14 by bclaeys           #+#    #+#             */
/*   Updated: 2025/02/07 14:52:48 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

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
