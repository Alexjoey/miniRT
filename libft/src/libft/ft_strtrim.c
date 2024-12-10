/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 16:51:52 by amylle            #+#    #+#             */
/*   Updated: 2023/10/22 17:28:00 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkset(char const c, char const *set)
{
	int	i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	while (s1[start] && checkset(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && checkset (s1[end - 1], set))
		end--;
	res = (char *)malloc((end - start + 1) * sizeof(*s1));
	if (!res)
		return (NULL);
	i = 0;
	while (start + i < end)
	{
		res[i] = s1[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
