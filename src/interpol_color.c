/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpol_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 00:15:33 by amylle            #+#    #+#             */
/*   Updated: 2025/01/04 00:15:34 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	ft_lerp(int start, int end, double percent)
{
	if (start == end)
		return (start);
	return ((int)(double) start + (end - start) * percent);
}

int	interpol_color(int scolor, int ecolor, double percent)
{
	int	r;
	int	g;
	int	b;

	r = ft_lerp((scolor >> 16) & 0xFF, (ecolor >> 16) & 0xFF, percent);
	g = ft_lerp((scolor >> 8) & 0xFF, (ecolor >> 8) & 0xFF, percent);
	b = ft_lerp(scolor & 0xFF, ecolor & 0xFF, percent);
	return ((r << 16) | (g << 8) | b);
}

int	rgb_to_int(int r, int g, int b)
{
	int	rt;
	int	gt;
	int	bt;

	rt = (r << 16) & 0x00FF0000;
	gt = (g << 8) & 0x0000FF00;
	bt = b & 0x000000FF;
	return (0xFF000000 | rt | gt | bt);
}
