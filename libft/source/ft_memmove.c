/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:03 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/10 19:21:09 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	t_byte	*to;
	t_byte	*from;
	t_byte	i;

	if (src == NULL || dest == NULL)
		return (NULL);
	to = (t_byte *) dest;
	from = (t_byte *) src;
	i = 0;
	if (to <= from)
		while (i++ < n)
			*to++ = *from++;
	else
	{
		while (n > 0)
		{
			*(to + n - 1) = *(from + n - 1);
			n--;
		}
	}
	return (dest);
}
