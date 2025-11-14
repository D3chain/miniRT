/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:12 by cgajean           #+#    #+#             */
/*   Updated: 2025/05/01 17:46:50 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	if (!n)
		return (0);
	while (*s1 && *s2 && *s1 == *s2 && n--)
	{
		s1++;
		s2++;
	}
	if (!n)
		return (*(unsigned char *)--s1 - *(unsigned char *)--s2);
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
