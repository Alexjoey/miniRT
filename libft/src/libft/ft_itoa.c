/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 15:08:22 by amylle            #+#    #+#             */
/*   Updated: 2023/10/25 15:57:49 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	intlen(int c)
{
	int	i;

	i = 0;
	if (c == 0)
		return (1);
	if (c < 0)
	{
		i++;
		c *= -1;
	}
	while (c > 0)
	{
		i++;
		c /= 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = intlen(n);
	str = (char *)malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	sign = 0;
	if (n < 0)
	{
		sign++;
		str[0] = '-';
		n *= -1;
	}
	str[i] = '\0';
	while (--i >= 0 + sign)
	{
		str[i] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}
