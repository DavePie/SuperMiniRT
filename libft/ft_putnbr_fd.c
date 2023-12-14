/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvandenb <dvandenb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 10:03:56 by dvandenb          #+#    #+#             */
/*   Updated: 2023/10/11 17:57:54 by dvandenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_recur_nbr(long n, int fd)
{
	if (!n)
		return ;
	ft_recur_nbr((int)(n / 10), fd);
	ft_putchar_fd((int)(n % 10) + '0', fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	long	temp;

	temp = n;
	if (n < 0)
	{
		temp *= -1;
		ft_putchar_fd('-', fd);
	}
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
		ft_recur_nbr(temp, fd);
}
