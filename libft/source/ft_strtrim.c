/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:59:14 by cgajean           #+#    #+#             */
/*   Updated: 2025/07/16 18:20:39 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_in_charset(const char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

static size_t	ft_size(char const **s, char const **tail, char const *set)
{
	size_t		size;
	char const	*ptr;

	size = 1;
	while (s && *s && **s && ft_in_charset(**s, set))
		(*s)++;
	ptr = *s;
	while (*tail && **tail)
		(*tail)++;
	while (ft_in_charset(**tail, set))
		(*tail)--;
	(*tail)--;
	while (ft_in_charset(**tail, set))
		(*tail)--;
	while (ptr <= *tail)
	{
		size++;
		ptr++;
	}
	return (size);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*str;
	char		*ptr_to_str;
	char const	*tail;
	size_t		size;

	if (s1 == NULL)
		return (NULL);
	tail = s1;
	if (set == NULL)
		size = ft_size(&s1, &tail, (char const *) "");
	else
		size = ft_size(&s1, &tail, set);
	str = ft_calloc(size, sizeof(char));
	if (str == NULL)
		return (NULL);
	ptr_to_str = str;
	while (s1 <= tail)
		*ptr_to_str++ = *s1++;
	*ptr_to_str = '\0';
	return (str);
}
