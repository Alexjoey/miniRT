/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 21:36:48 by amylle            #+#    #+#             */
/*   Updated: 2025/01/03 22:13:33 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <math.h>

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vector;

t_vector	set_vector(float x, float y, float z);
t_vector	add_vector(t_vector a, t_vector b);
t_vector	subtract_vector(t_vector a, t_vector b);
t_vector	multiply_vector(t_vector a, float scalar);

t_vector	normalize_vector(t_vector a);
float		dot_product(t_vector a, t_vector b);
t_vector	cross_product(t_vector a, t_vector b);
float		length_vector_squared(t_vector a);
float		length_vector(t_vector a);
