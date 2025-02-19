/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 23:12:17 by amylle            #+#    #+#             */
/*   Updated: 2025/01/03 23:12:18 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	set_vector(float x, float y, float z)
{
	return ((t_vector){x, y, z});
}

t_vector	add_vector(t_vector a, t_vector b)
{
	return ((t_vector){a.x + b.x, a.y + b.y, a.z + b.z});
}

t_vector	subtract_vector(t_vector a, t_vector b)
{
	return ((t_vector){a.x - b.x, a.y - b.y, a.z - b.z});
}

t_vector	multiply_vector(t_vector a, float scalar)
{
	return ((t_vector){a.x * scalar, a.y * scalar, a.z * scalar});
}

t_vector	divide_vector(t_vector a, float scalar)
{
	return ((t_vector){a.x / scalar, a.y / scalar, a.z / scalar});
}
