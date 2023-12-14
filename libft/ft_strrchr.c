/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 20:07:38 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/09 13:44:58 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*ans;

	ans = 0;
	while (*s)
	{
		if (*s == (char)c)
			ans = (char *)s;
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (ans);
}
