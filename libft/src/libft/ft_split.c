/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 17:41:21 by amylle            #+#    #+#             */
/*   Updated: 2023/10/28 17:55:29 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static size_t	word_count(char const *s, char c)
{
	size_t	count;
	int		skip;
	int		i;

	skip = 1;
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && skip == 1)
		{
			count++;
			skip = 0;
		}
		else if (s[i] == c)
			skip = 1;
		i++;
	}
	return (count);
}

static void	make_words(char **words, char const *s, char c, size_t wrdcnt)
{
	char	*ptr;

	while (*s == c && *s)
		s++;
	while (wrdcnt--)
	{
		ptr = ft_strchr(s, c);
		if (ptr)
		{
			*words = ft_substr(s, 0, ptr - s);
			while (*ptr == c && *ptr)
				ptr++;
			s = ptr;
		}
		else
			*words = ft_substr(s, 0, ft_strlen(s) + 1);
		words++;
	}
	*words = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	wrdcnt;

	if (s == NULL)
		return (NULL);
	wrdcnt = word_count(s, c);
	ret = malloc(sizeof(char *) * (wrdcnt + 1));
	if (!ret)
		return (NULL);
	make_words(ret, s, c, wrdcnt);
	return (ret);
}
