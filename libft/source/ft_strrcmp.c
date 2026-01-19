/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:19:38 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 16:19:40 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strrcmp(const char *s1, const char *s2)
{
	int	pos_s1;
	int	pos_s2;

	pos_s1 = ft_strlen(s1) - 1;
	pos_s2 = ft_strlen(s2) - 1;
	while (pos_s1 >= 0 && pos_s2 >= 0)
	{
		if (s1[pos_s1] != s2[pos_s2])
			return (s1[pos_s1] - s2[pos_s2]);
		pos_s1--;
		pos_s2--;
	}
	return (0);
}
