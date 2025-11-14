/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 10:58:59 by cgajean           #+#    #+#             */
/*   Updated: 2025/11/13 17:57:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

ssize_t	ft_putstr_fd(char *s, int fd)
{
	ssize_t	count;

	if (s == NULL || fd < 0)
		return (0);
	count = 0;
	while (*s)
		count += ft_putchar_fd(fd, *s++);
	return (count);
}
