/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:52:17 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/14 14:52:56 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <math.h>

float	ft_atof(char *str)
{
	float	nb;
	int		i;
	int		sign;

	nb = 0;
	i = 0;
	sign = 1;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] && str[i] != '.')
	{
		nb = nb * 10 + str[i] - '0';
		i++;
	}
	if (str[i] == '.')
		nb += (float)ft_atoi(&str[i + 1]) / pow(10, ft_strlen(&str[i + 1]));
	return (nb * sign);
}
