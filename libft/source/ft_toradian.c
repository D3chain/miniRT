/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toradian.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:21:55 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 17:31:08 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef _MATH_H
# define PI 3.14159265358979323846
#else
# define PI M_PI
#endif

t_real	ft_toradian(t_real angle)
{
	static const t_real	term = PI / 180;

	return (angle * term);
}
