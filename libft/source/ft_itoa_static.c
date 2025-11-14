/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_static.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:58:50 by cgajean           #+#    #+#             */
/*   Updated: 2025/07/16 11:28:53 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_itoa_static(int n, char *str)
{
	char	*ptr_to_str;
	long	nbr;
	size_t	nbr_len;

	if (str)
	{
		nbr = n;
		nbr_len = ft_nbrlen(nbr);
		if (nbr < 0)
		{
			*str = '-';
			nbr *= -1;
		}
		ptr_to_str = &str[nbr_len];
		*ptr_to_str-- = '\0';
		if (nbr == 0)
			*ptr_to_str = '0';
		while (nbr > 0)
		{
			*ptr_to_str-- = nbr % 10 + '0';
			nbr /= 10;
		}
	}
}
