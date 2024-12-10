/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_highhex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:50:31 by amylle            #+#    #+#             */
/*   Updated: 2024/02/16 19:14:22 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_highhex(unsigned int i)
{
	char	*str;
	int		len;

	str = ft_itoa_base(i, "0123456789ABCDEF");
	if (!str)
		return (0);
	len = ft_format_str(str);
	free (str);
	return (len);
}
