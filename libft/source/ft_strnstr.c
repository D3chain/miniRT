/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:14 by cgajean           #+#    #+#             */
/*   Updated: 2025/04/30 10:53:36 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_init(const char *big, const char *little, size_t len, \
	size_t *little_len)
{
	if (!len || big == NULL || little == NULL)
		return (0);
	*little_len = ft_strlen(little);
	if (*little_len > len)
		return (0);
	return (1);
}

static void	ft_place_end(const char **str_ptr, const char **end_ptr, size_t n)
{
	*end_ptr = *str_ptr;
	while (**end_ptr && n-- > 0)
		(*end_ptr)++;
}

static int	ft_compare(const char *big, const char *little, size_t little_len)
{
	size_t		n;

	n = 1;
	while (n < little_len)
	{
		if (*(big + n) != *(little + n))
			return (0);
		n++;
	}
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		little_len;
	const char	*end_ptr;

	if (*little == '\0')
		return ((char *) big);
	if (ft_init(big, little, len, &little_len) == 0)
		return (NULL);
	ft_place_end(&big, &end_ptr, len);
	while (big + little_len <= end_ptr)
	{
		if (*little == *big)
		{
			if (ft_compare(big, little, little_len) == 1)
				return ((char *) big);
			else
				big++;
		}
		else
				big++;
	}
	return (NULL);
}
