/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrncmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:19:48 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 16:19:50 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrncmp(const char *s1, const char *s2, size_t size)
{
	int	pos_s1;
	int	pos_s2;

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
