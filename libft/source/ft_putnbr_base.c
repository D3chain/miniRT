/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:22:45 by cgajean           #+#    #+#             */
/*   Updated: 2025/11/13 18:10:28 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printnbr_base(int nbr, int base, char *base_charset, \
																int *count)
{
	long long	nb;

	nb = nbr;
	if (nb < 0)
	{
		*count += ft_putchar('-');
		nb *= -1;
	}
	if (nb >= 16)
	{
		ft_printnbr_base(nb / 16, base, base_charset, count);
		ft_printnbr_base(nb % 16, base, base_charset, count);
	}
	else
		*count += ft_putchar(base_charset[nb]);
}

ssize_t	ft_putnbr_base(int nbr, char *base_charset)
{
	int	count;
	int	base;

	base = (int) ft_strlen(base_charset);
	if (!base)
		return (0);
	count = 0;
	ft_printnbr_base(nbr, base, base_charset, &count);
	return (count);
}
