/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:40:43 by amylle            #+#    #+#             */
/*   Updated: 2024/06/05 13:40:45 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	scalc(int start, int end)
{
	if (start < end)
		return (1);
	else
		return (-1);
}

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
