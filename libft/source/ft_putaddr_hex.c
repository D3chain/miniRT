/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddr_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:14:26 by cgajean           #+#    #+#             */
/*   Updated: 2025/11/13 18:10:46 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_printaddr_hex(uintptr_t addr, ssize_t *count)
{
	if (addr >= 16)
	{
		ft_printaddr_hex(addr / 16, count);
		ft_printaddr_hex(addr % 16, count);
	}
	else
		*count += ft_putchar("0123456789abcdef"[addr]);
}

ssize_t	ft_putaddr_hex(uintptr_t addr)
{
	ssize_t	count;

	if (addr == 0)
		count = ft_putstr("(nil)");
	else
	{
		count = ft_putstr("0x");
		ft_printaddr_hex(addr, &count);
	}
	return (count);
}
