/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_and_ambient.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bclaeys <bclaeys@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:37:06 by bclaeys           #+#    #+#             */
/*   Updated: 2025/02/07 18:38:19 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	add_color(t_hit *hit, float operatee, t_color orig_col, char operator)
{
	if (operator == '*')
	{
		hit->color.r *= operatee;
		hit->color.g *= operatee;
		hit->color.b *= operatee;
	}
	if (operator == '+')
	{
		hit->color.r += orig_col.r * operatee;
		hit->color.g += orig_col.g * operatee;
		hit->color.b += orig_col.b * operatee;
	}
	return (0);
}

void	cap_ambient(t_hit *hit)
{
	if (hit->color.r > 255)
		hit->color.r = 255;
	if (hit->color.g > 255)
		hit->color.g = 255;
	if (hit->color.b > 255)
		hit->color.b = 255;
}
