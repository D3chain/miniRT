/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:15 by cgajean           #+#    #+#             */
/*   Updated: 2025/05/01 15:28:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*tail;

	if (s == NULL)
		return (NULL);
	tail = s;
	while (*tail)
		tail++;
	if ((char) c == '\0')
		return ((char *) tail);
	while (s <= tail)
	{
		if (*tail == (char) c)
			return ((char *) tail);
		else
			tail--;
	}
	return (NULL);
}
