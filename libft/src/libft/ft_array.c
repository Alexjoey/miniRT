/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <alexm@live.be>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:57:39 by amylle            #+#    #+#             */
/*   Updated: 2024/07/24 16:03:03 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

void	ft_freearray(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
		free (array[i]);
	free (array);
}

char	**ft_duparray(char **array)
{
	int		i;
	char	**ret;

	i = 0;
	while (array[i])
		i++;
	ret = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (array[++i])
		ret[i] = ft_strdup(array[i]);
	return (ret);
}
