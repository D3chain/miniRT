/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:58:44 by cgajean           #+#    #+#             */
/*   Updated: 2025/11/13 18:10:59 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printnbr(int fd, int nbr, ssize_t *count)
{
	long	nb;

	nb = nbr;
	if (nb < 0)
	{
		ft_putchar('-');
		nb *= -1;
		(*count)++;
	}
	if (nb >= 10)
	{
		ft_printnbr(fd, nb / 10, count);
		ft_printnbr(fd, nb % 10, count);
	}
	else
		*count += ft_putchar_fd(fd, "0123456789"[nb]);
}

ssize_t	ft_putnbr_fd(int n, int fd)
{
	ssize_t	count;

	count = 0;
	ft_printnbr(fd, n, &count);
	return (count);
}
