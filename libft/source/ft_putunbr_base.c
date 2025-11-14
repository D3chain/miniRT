/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 19:22:45 by cgajean           #+#    #+#             */
/*   Updated: 2025/11/13 17:59:50 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printunbr_base(unsigned int nbr, size_t base, \
	char *base_charset, ssize_t *count)
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
		ft_printunbr_base(nb / 16, base, base_charset, count);
		ft_printunbr_base(nb % 16, base, base_charset, count);
	}
	else
		*count += ft_putchar(base_charset[nb]);
}

ssize_t	ft_putunbr_base(unsigned int nbr, char *base_charset)
{
	ssize_t	count;
	size_t	base;

	base = ft_strlen(base_charset);
	if (!base)
		return (0);
	count = 0;
	ft_printunbr_base(nbr, base, base_charset, &count);
	return (count);
}
