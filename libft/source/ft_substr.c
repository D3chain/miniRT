/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:59:18 by cgajean           #+#    #+#             */
/*   Updated: 2025/05/02 15:12:04 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_size(const char **s, unsigned int start, size_t len)
{
	size_t		size;
	size_t		n;
	const char	*ptr_to_s;

	size = 0;
	n = 0;
	if (start > ft_strlen(*s))
		return (0);
	while (len && **s && n < start)
	{
		(*s)++;
		n++;
	}
	if (len && n == start)
	{
		ptr_to_s = *s;
		n = 0;
		while (*ptr_to_s++ && n++ < len)
			size++;
	}
	return (size);
}

static void	ft_write_substr(char *to, const char *from, size_t size)
{
	while (*from && size-- > 0)
		*to++ = *from++;
	*to = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*substr;
	size_t		size;

	if (s == NULL)
		return (NULL);
	size = ft_get_size(&s, start, len);
	substr = malloc((size + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	ft_write_substr(substr, s, size);
	return (substr);
}
