/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:28:57 by cgajean           #+#    #+#             */
/*   Updated: 2025/04/29 12:44:40 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*str;

	if (s == NULL)
		return (NULL);
	str = (const char *) s;
	while (n-- > 0)
	{
		if (*str == (char) c)
			return ((void *) str);
		else
			str++;
	}
	return (NULL);
}
