/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:59:12 by cgajean           #+#    #+#             */
/*   Updated: 2025/04/30 17:44:59 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t			len;
	unsigned int	n;
	char			*str;
	char			*ptr_to_str;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	str = malloc((len + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	ptr_to_str = str;
	n = 0;
	while (*s)
	{
		*ptr_to_str++ = f(n, *s);
		n++;
		s++;
	}
	*ptr_to_str = '\0';
	return (str);
}
