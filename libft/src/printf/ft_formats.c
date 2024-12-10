/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_formats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:15:09 by amylle            #+#    #+#             */
/*   Updated: 2024/02/21 23:58:23 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_formats(char c, va_list args)
{
	int	i;

	i = 0;
	if (c == 'c')
		i = ft_format_char(va_arg(args, int));
	else if (c == 's')
		i = ft_format_str(va_arg(args, char *));
	else if (c == 'p')
		i = ft_format_pointer(va_arg(args, void *));
	else if (c == 'd')
		i = ft_format_decimal(va_arg(args, int));
	else if (c == 'i')
		i = ft_format_int(va_arg(args, int));
	else if (c == 'u')
		i = ft_format_unsigned_decimal(va_arg(args, unsigned int));
	else if (c == 'x')
		i = ft_format_lowhex(va_arg(args, unsigned int));
	else if (c == 'X')
		i = ft_format_highhex(va_arg(args, unsigned int));
	else if (c == '%')
		i = ft_format_char('%');
	return (i);
}
