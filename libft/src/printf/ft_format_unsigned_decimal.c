/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_unsigned_decimal.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 16:09:30 by amylle            #+#    #+#             */
/*   Updated: 2024/02/16 19:13:49 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_unsigned_decimal(unsigned int n)
{
	char	*str;
	int		len;

	str = ft_itoa_base(n, "0123456789");
	if (!str)
		return (0);
	len = ft_format_str(str);
	free (str);
	return (len);
}
