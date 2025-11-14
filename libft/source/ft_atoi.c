/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:28:33 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/19 10:26:56 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_skippspaces(const char **nptr)
{
	while (**nptr && ft_isspace(**nptr))
		(*nptr)++;
}

int	ft_atoi(const char *nptr)
{
	long	result;
	int		sign;

	if (nptr == NULL)
		return (0);
	ft_skippspaces(&nptr);
	sign = 1;
	result = 0;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign *= -1;
		nptr++;
	}
	while (*nptr && ft_isdigit(*nptr))
		result = result * 10 + (*nptr++ - '0');
	return (result * sign);
}
