/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 12:16:33 by amylle            #+#    #+#             */
/*   Updated: 2025/01/15 15:24:35 by bclaeys          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	ft_atoi_base(char *num, char *base)
{
	int	ret;
	int	i;
	int	j;
	int	baselen;

	baselen = ft_strlen(base);
	ret = 0;
	i = -1;
	while (num[++i])
	{
		j = -1;
		while (base[++j])
			if (base[j] == num[i])
				ret += ret * baselen + j;
	}
	return (ret);
}
