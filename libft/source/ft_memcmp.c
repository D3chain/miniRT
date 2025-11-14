/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:28:59 by cgajean           #+#    #+#             */
/*   Updated: 2025/05/02 14:50:52 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	t_byte	*mem1;
	t_byte	*mem2;

	if (s1 == NULL || s2 == NULL || n == 0)
		return (0);
	mem1 = (t_byte *) s1;
	mem2 = (t_byte *) s2;
	while (n && *mem1 == *mem2)
	{
		mem1++;
		mem2++;
		n--;
	}
	if (!n)
		return (*--mem1 - *--mem2);
	else
		return (*mem1 - *mem2);
}
