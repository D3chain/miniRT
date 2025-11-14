/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:01 by cgajean           #+#    #+#             */
/*   Updated: 2025/05/02 16:51:10 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	t_byte	*to;
	t_byte	*from;

	if (src && dest)
	{
		to = (t_byte *) dest;
		from = (t_byte *) src;
		while (n-- != 0)
			*to++ = *from++;
	}
	return (dest);
}
