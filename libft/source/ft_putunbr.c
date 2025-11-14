/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:13:42 by cgajean           #+#    #+#             */
/*   Updated: 2025/11/13 18:10:00 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printunbr(unsigned int nbr, ssize_t *count)
{
	long long	nb;

	nb = nbr;
	if (nb < 0)
	{
		count += ft_putchar('-');
		nb *= -1;
	}
	if (nb >= 10)
	{
		ft_printunbr(nb / 10, count);
		ft_printunbr(nb % 10, count);
	}
	else
		*count += ft_putchar("0123456789"[nb]);
}

ssize_t	ft_putunbr(unsigned int nbr)
{
	ssize_t	count;

	count = 0;
	ft_printunbr(nbr, &count);
	return (count);
}
