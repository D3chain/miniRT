/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/05/01 18:14:51 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;

	if (!src)
		return (0);
	src_len = ft_strlen(src);
	if (!dst || !size)
		return (src_len);
	else
	{
		while (*src && --size > 0)
			*dst++ = *src++;
		*dst = '\0';
	}
	return (src_len);
}
