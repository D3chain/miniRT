/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:58:50 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/19 10:26:18 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	char	*ptr_to_str;
	long	nbr;
	size_t	nbr_len;

	nbr = n;
	nbr_len = ft_nbrlen(nbr);
	str = malloc((nbr_len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
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
	return (str);
}
