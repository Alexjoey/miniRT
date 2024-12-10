/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_lowhex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 13:45:40 by amylle            #+#    #+#             */
/*   Updated: 2024/02/16 19:14:13 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_format_lowhex(unsigned int i)
{
	char	*str;
	int		strlen;

	str = ft_itoa_base(i, "0123456789abcdef");
	if (!str)
		return (0);
	strlen = ft_format_str(str);
	free (str);
	return (strlen);
}
