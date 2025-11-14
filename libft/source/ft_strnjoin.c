/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:34:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/05/22 17:35:15 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*str;
	char	*str_ptr;
	size_t	size;

	if (!s1 && !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = ft_calloc(size, sizeof(char));
	if (!str)
		return (NULL);
	str_ptr = str;
	while (*s1)
		*str_ptr++ = *s1++;
	while (n-- && *s2)
		*str_ptr++ = *s2++;
	*str_ptr = '\0';
	return (str);
}
