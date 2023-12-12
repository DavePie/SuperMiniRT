/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 16:09:39 by dvandenb          #+#    #+#             */
/*   Updated: 2023/12/12 16:34:20 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_error(int condition, char *mess, char *val)
{
	if (condition)
	{
		write(2, "error: ", 7);
		while (*mess)
			write(2, mess++, 1);
		while (val && *val)
			write(2, val++, 1);
		write(2, "\n", 1);
		exit(1);
	}
}
