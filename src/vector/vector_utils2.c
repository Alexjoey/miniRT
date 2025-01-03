/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:12:38 by amylle            #+#    #+#             */
/*   Updated: 2025/01/03 23:12:43 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

float	dot_product(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vector	cross_product(t_vector a, t_vector b)
{
	t_vector	ret;

	ret.x = a.y * b.z - a.z * b.y;
	ret.y = a.z * b.x - a.x * b.z;
	ret.z = a.x * b.y - a.y * b.x;
	return (ret);
}

float	length_vector_squared(t_vector a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

float	length_vector(t_vector a)
{
	return (sqrtf(length_vector_squared(a)));
}
