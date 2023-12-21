/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 08:59:33 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/21 11:29:11 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_is_number(char *s, int dotted)
{
	if (*s == '-')
	{
		s++;
		if (!*s)
			return (0);
	}
	while (*s && *s != '\n')
	{
		if (!ft_isdigit(*s) && !(dotted && *s == '.'))
			return (0);
		s++;
	}
	return (1);
}
