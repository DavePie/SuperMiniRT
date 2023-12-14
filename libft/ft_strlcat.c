/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 13:50:42 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/10 13:58:37 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcat(char *dest, const char *src, unsigned long int size)
{
	unsigned int	len;
	unsigned int	s;

	if (!size && !src)
		return (0);
	s = size;
	len = 0;
	while (s > 0 && *dest != '\0')
	{
		dest++;
		len++;
		s--;
	}
	while (s > 1 && *src != '\0')
	{
		*dest++ = *src++;
		s--;
		len++;
	}
	while (*src++ != '\0')
		len++;
	if (s > 0)
		*dest = '\0';
	return (len);
}
