/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:11:31 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/10 13:19:37 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle,
size_t len)
{
	char	*hay;
	char	*need;
	size_t	l;

	if (!*needle)
		return ((char *)haystack);
	while (len > 0 && *haystack)
	{
		hay = (char *)haystack;
		need = (char *)needle;
		l = len;
		while (*(need++) == *(hay++) && l-- > 0)
			if (*need == '\0')
				return ((char *)haystack);
		len--;
		haystack++;
	}
	return (0);
}
