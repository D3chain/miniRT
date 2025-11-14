/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:37:38 by cgajean           #+#    #+#             */
/*   Updated: 2025/11/13 17:57:36 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putstr(char *str)
{
	ssize_t	count;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	else
	{
		count = 0;
		while (*str)
		{
			write(1, str++, 1);
			count++;
		}
	}
	return (count);
}
