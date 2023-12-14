/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 18:08:02 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/11 17:57:04 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		l;
	char	*ans;

	l = ft_strlen(s);
	ans = malloc(sizeof(char) * (l + 1));
	if (!ans)
		return (0);
	ans[l] = '\0';
	if (!ans)
		return (0);
	while (--l >= 0)
		ans[l] = f(l, s[l]);
	return (ans);
}
