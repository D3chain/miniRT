/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:06:23 by cgajean           #+#    #+#             */
/*   Updated: 2025/07/16 16:07:31 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_base_is_conform(const char *base)
{
	char	symbols[100];
	char	*cur;
	char	*parse_ptr;
	int		i;
	int		base_len;

	base_len = ft_strlen(base);
	i = 99;
	while (i--)
		symbols[i] = '\0';
	if (base_len == 0 || base_len == 1)
		return (0);
	cur = symbols;
	while (*base)
	{
		if (*base == '+' || *base == '-'
			|| (*base > 8 && *base < 14) || *base == 32)
			return (false);
		parse_ptr = symbols;
		while (*parse_ptr)
			if (*base == *parse_ptr++)
				return (false);
		*cur++ = *base++;
	}
	return (true);
}

static int	ft_base_index(char c, const char *base)
{
	int		index;

	index = 0;
	while (*base)
	{
		if (c == *base++)
			return (index);
		index++;
	}
	return (-1);
}

static int	ft_get_sign(const char **str)
{
	int		sign;

	sign = 0;
	while (**str == '+' || **str == '-')
		if (*(*str)++ == '-')
			sign++;
	if (sign % 2)
		return (-1);
	else
		return (1);
}

int	ft_atoi_base(const char *nptr, const char *base)
{
	int		sign;
	char	*tail;
	int		total;
	int		base_val;

	if (base)
		base = ft_tolower_str((char *) base);
	if (!ft_base_is_conform(base))
		return (0);
	base_val = ft_strlen(base);
	while (*nptr && ((*nptr > 8 && *nptr < 14) || *nptr == 32))
		nptr++;
	sign = ft_get_sign(&nptr);
	tail = (char *) nptr;
	total = 0;
	while (ft_base_index(*tail, base) != -1)
		tail++;
	while (nptr < tail)
		total = total * base_val + ft_base_index(*nptr++, base);
	return (sign * total);
}
