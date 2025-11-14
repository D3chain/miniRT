/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:08 by cgajean           #+#    #+#             */
/*   Updated: 2025/05/02 16:15:00 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	n;

	n = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (size != 0 && dst != NULL && src != NULL)
	{
		while (*dst)
		{
			dst++;
			n++;
		}
		while (*src && n++ < size - 1)
			*dst++ = *src++;
		if (dst != NULL)
			*dst = '\0';
	}
	return (src_len + ft_min(dst_len, size));
}
