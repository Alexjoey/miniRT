/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_project.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:41:02 by amylle            #+#    #+#             */
/*   Updated: 2024/06/05 13:41:03 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

static void	ft_rotate_x_axis(int *y, int *z, double angle)
{
	int	temp_y;

	temp_y = *y;
	*y = temp_y * cos(angle) + *z * sin(angle);
	*z = temp_y * -sin(angle) + *z * cos(angle);
}

static void	ft_rotate_y_axis(int *x, int *z, double angle)
{
	int	temp_x;

	temp_x = *x;
	*x = temp_x * cos(angle) + *z * sin(angle);
	*z = temp_x * -sin(angle) + *z * cos(angle);
}

static void	ft_rotate_z_axis(int *x, int *y, double angle)
{
	int	temp_x;
	int	temp_y;

	temp_x = *x;
	temp_y = *y;
	*x = temp_x * cos(angle) - temp_y * sin(angle);
	*y = temp_x * sin(angle) + temp_y * cos(angle);
}
