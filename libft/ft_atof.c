/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-oli <alde-oli@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:52:17 by alde-oli          #+#    #+#             */
/*   Updated: 2023/12/14 17:18:50 by alde-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static float	convert_integer_part(char **str)
{
	float	result;

	result = 0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static float	convert_fractional_part(char **str)
{
	float	fraction;
	float	result;

	fraction = 0.1f;
	result = 0;
	while (**str >= '0' && **str <= '9')
	{
		result += (**str - '0') * fraction;
		fraction *= 0.1f;
		(*str)++;
	}
	return (result);
}

static int	skip_spaces(char **str)
{
	int	sign;

	sign = 1;
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	return (sign);
}

float	ft_atof(char *str)
{
	int		sign;
	float	integer_part;
	float	fractional_part;

	sign = skip_spaces(&str);
	integer_part = convert_integer_part(&str);
	if (*str == '.')
		str++;
	fractional_part = convert_fractional_part(&str);
	return (sign * (integer_part + fractional_part));
}
