/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 19:12:57 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/09 15:10:52 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	len;

	len = 0;
	if (size > 0)
	{
		while (size - 1 > 0 && *src != '\0')
		{
			*dest = *src;
			dest++;
			src++;
			len++;
			size--;
		}	
		*dest = '\0';
	}
	while (*src != '\0')
	{
		src++;
		len++;
	}
	return (len);
}
