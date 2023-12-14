/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 16:24:36 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/10 13:05:52 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *add, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)add;
	while (len-- > 0)
		*(ptr++) = (unsigned char)c;
	return (add);
}
