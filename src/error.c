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
#include <unistd.h>

int	ft_error(char *str, char *filename)
{
	ft_putstr_fd(str, STDERR_FILENO);
	if (filename)
		ft_putendl_fd(filename, STDERR_FILENO);
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
