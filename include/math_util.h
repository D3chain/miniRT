/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:03:29 by echatela          #+#    #+#             */
/*   Updated: 2025/11/18 11:28:46 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTIL_H
# define MATH_UTIL_H

# include "minirt.h"

typedef struct s_poly2_root
{
	int	n;
	double	r1;
	double	r2;
}	t_poly2_root;

double		dot(t_double3 a, t_double3 b);
t_double3	dot3(t_double3 a, t_double3 b);
t_double3	plus3(t_double3 a, t_double3 b);
t_double3	minus3(t_double3 a, t_double3 b);

#endif
