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

typedef struct s_sol2
{
	int	n;
	double	r1;
	double	r2;
}	t_sol2;

double			dot(t_double3 a, t_double3 b);
double			sqdot(t_double3 v);

t_double3		dot3(t_double3 a, t_double3 b);
t_double3		plus3(t_double3 a, t_double3 b);
t_double3		minus3(t_double3 a, t_double3 b);
t_double3		mul3(t_double3 a, double factor);
t_double3		cross3(t_double3 a, t_double3 b);

t_sol2			polynome2(double a, double b, double c);

t_double3		normalize3(t_double3 v);

t_double3		project(const t_double3 origin, const t_double3 dir, const double dst);
t_double3		orient_normal(t_double3 normal, t_double3 ray);
double			norm3(t_double3 vec);
t_color			color_add(t_color color1, t_color color2);
t_color			mul_color(t_color color, t_color light, double factor);

#endif
