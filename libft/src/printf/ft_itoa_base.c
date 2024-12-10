/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:21:29 by amylle            #+#    #+#             */
/*   Updated: 2023/12/11 18:57:21 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_base(unsigned long long n, char *base)
{
	int					num_len;
	unsigned long long	base_len;
	char				*str;
	unsigned long long	temp;

	temp = n;
	base_len = ft_strlen(base);
	num_len = 1;
	while (temp >= base_len)
	{
		temp /= base_len;
		num_len++;
	}
	str = ft_calloc((num_len + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (num_len)
	{
		num_len--;
		str[num_len] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}
