/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:26:13 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/19 10:26:14 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen_base(long nbr, int base)
{
	size_t	len;

	if (base > 0)
	{
		len = 1;
		nbr = (long) nbr;
		if (nbr < 0)
		{
			nbr *= -1;
			len++;
		}
		while (nbr >= base)
		{
			len++;
			nbr /= base;
		}
		return (len);
	}
	else
		return (0);
}
