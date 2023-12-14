/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 11:41:55 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/11 17:57:27 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;
	char	*start;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	start = dup;
	if (!dup)
		return (0);
	while (*s1)
		*(dup++) = *(s1++);
	*dup = '\0';
	return (start);
}
