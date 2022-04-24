/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eozben <eozben@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 14:52:43 by eozben            #+#    #+#             */
/*   Updated: 2022/01/15 22:46:53 by eozben           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcpy(char *dst, char *src, int n)
{
	int	i;

	i = 0;
	while (i <= n)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*free_str(char *str)
{
	free(str);
	return (NULL);
}
