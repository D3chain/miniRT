/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mathematics.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 17:15:41 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 16:57:47 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATHEMATICS_H
# define MATHEMATICS_H

# include "minirt_typedef.h"
# include "types.h"

struct s_sol2
{
	int		n;
	t_real	r1;
	t_real	r2;
};

/*	vec_op_1.c	*/
t_real3	plus3(t_real3 a, t_real3 b);
t_real3	minus3(t_real3 a, t_real3 b);
t_real3	vmul3(t_real3 a, t_real3 b);
t_real3	cross3(t_real3 a, t_real3 b);
t_real3	normalize3(t_real3 v);

/*	vec_op_2.c	*/
t_real3	fmul3(t_real3 a, t_real factor);
t_real3	fplus3(t_real3 a, t_real factor);
t_real3	reflect(t_real3 incident, t_real3 normal);
t_real3	project(t_real3 origin, t_real3 dir, t_real dst);

/*	vec_op_3.c	*/
t_real3	orient_normal(t_real3 normal, t_real3 ray);
t_real	norm3(t_real3 vec);
t_real	dot(t_real3 a, t_real3 b);
t_real	sqdot(t_real3 v);

/*	polynome2.c	*/
t_sol2	polynome2(t_real a, t_real b, t_real c);

#endif
