/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toradian.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 10:33:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/11/17 18:14:49 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifndef _MATH_H
# define PI 3.14159265358979323846
#else
# define PI M_PI
#endif

double	ft_toradian(double angle)
{
	return (angle * PI / 180);
}
