/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toradian.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:33:51 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/18 22:18:44 by fox              ###   ########.fr       */
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
	static const t_real	PI_OVER_180 = PI / 180;
	
	return (angle * PI_OVER_180);
}
