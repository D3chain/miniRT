/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmprev.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:09:26 by fox               #+#    #+#             */
/*   Updated: 2025/11/14 18:19:28 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrncmp(const char *s1, const char *s2, size_t size)
{
	size_t	pos_s1;
	size_t	pos_s2;

	if (size > 0)
	{
		pos_s1 = ft_strlen(s1) - 1;
		pos_s2 = ft_strlen(s2) - 1;
		while (size > 0 && pos_s1 >= 0 && pos_s2 >= 0)
		{
			if (s1[pos_s1] != s2[pos_s2])
				return (s1[pos_s1] - s2[pos_s2]);
			pos_s1--;
			pos_s2--;
			size--;
		}
	}
	return (0);
}
