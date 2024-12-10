/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 14:36:28 by amylle            #+#    #+#             */
/*   Updated: 2023/12/11 18:23:13 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "./libft.h"

int		ft_formats(char c, va_list args);
int		ft_printf(const char *str, ...);
int		ft_isformat(const unsigned int c);
int		ft_format_char(int c);
int		ft_format_str(char *str);
int		ft_format_decimal(int i);
int		ft_format_int(int i);
int		ft_format_unsigned_decimal(unsigned int i);
char	*ft_itoa_base(unsigned long long n, char *base);
int		ft_format_lowhex(unsigned int i);
int		ft_format_highhex(unsigned int i);
int		ft_format_pointer(void *yom);

#endif
