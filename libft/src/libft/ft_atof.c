/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:35:20 by amylle            #+#    #+#             */
/*   Updated: 2025/01/10 17:44:11 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

//very basic atof
float	ft_atof(const char	*str)
{
	float	ret;
	float	sign;
	float	pow;
	int		i;

	i = 0;
	sign = 1.0;
	if (str[i] == '-')
	{
		sign = -1.0;
		i++;
	}
	ret = 0.0;
	while (str[i] >= '0' && str[i] <= '9')
		ret = ret * 10 + (str[i++] - '0');
	if (str[i++] == '.')
	{
		pow = 10.0;
		while (str[i] >= '0' && str[i] <= '9')
		{
			ret += (str[i++] - '0') / pow;
			pow *= 10.0;
		}
	}
	return (sign * ret);
}
