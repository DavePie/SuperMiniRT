/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 11:35:01 by alde-oli          #+#    #+#             */
/*   Updated: 2023/11/20 11:35:29 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *src, int i)
{
	int		j;
	char	*dest;

	j = 0;
	dest = ft_calloc((i + 2), sizeof(char));
	if (!dest)
		return (NULL);
	while (j <= i && src[j])
	{
		dest[j] = src[j];
		j++;
	}
	return (dest);
}
