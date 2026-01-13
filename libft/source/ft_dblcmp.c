/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dblcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 16:31:50 by echatela          #+#    #+#             */
/*   Updated: 2026/01/13 17:13:39 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	ft_dblcmp(double d1, double d2, double epsilon)
{
	const double	dif = d1 - d2;

	if (ft_dabs(dif) < epsilon)
		return (0.0);
	return (dif);
}
