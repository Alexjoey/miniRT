/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amylle <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 13:40:33 by amylle            #+#    #+#             */
/*   Updated: 2024/06/05 13:40:38 by amylle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	ft_error(char *str, char *filename)
{
	ft_putstr_fd(str, 1);
	ft_putendl_fd(filename, 1);
	return (false);
}

void	ft_freestrarray(char **strarray)
{
	int	i;

	i = -1;
	while (strarray[++i])
		free (strarray[i]);
	free (strarray);
}
