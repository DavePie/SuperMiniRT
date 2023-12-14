/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:36:17 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/11 17:57:18 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*ans;
	size_t	i;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ans = malloc(s1len + s2len + 1);
	if (!ans)
		return (0);
	i = -1;
	while (++i < s1len)
		ans[i] = s1[i];
	i = -1;
	while (++i < s2len)
		ans[i + s1len] = s2[i];
	ans[i + s1len] = '\0';
	return (ans);
}
