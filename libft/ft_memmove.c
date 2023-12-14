/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 19:55:11 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/11 17:58:45 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*to;
	const char	*from;

	to = dst;
	from = src;
	if (from > to)
		return (ft_memcpy(dst, src, len));
	if (from == to)
		return (dst);
	while (len > 0)
	{
		to[len - 1] = from[len - 1];
		len--;
	}
	return (dst);
}
