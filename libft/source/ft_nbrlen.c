/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 10:25:56 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/19 10:25:57 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(long nbr)
{
	size_t	len;

	len = 1;
	nbr = (long) nbr;
	if (nbr < 0)
	{
		nbr *= -1;
		len++;
	}
	while (nbr >= 10)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}
