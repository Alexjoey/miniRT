/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_pointer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 14:45:09 by amylle            #+#    #+#             */
/*   Updated: 2024/02/22 00:27:54 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_pointer(void *ptr)
{
	int				len;
	char			*str;

	if (ptr == NULL)
	{
		len = ft_format_str("(nil)");
		return (len);
	}
	str = ft_itoa_base((unsigned long)ptr, "0123456789abcdef");
	if (!str)
		return (0);
	len = ft_format_str("0x");
	len += ft_format_str(str);
	free (str);
	return (len);
}
