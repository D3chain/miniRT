/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit_dst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:25:18 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 20:02:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((always_inline))
inline t_real	closest_hit_dst_dbl(const t_real a, const t_real b)
{
	if (a < EPSILON && b < EPSILON)
		return (-FLT_1);
	if (a < EPSILON)
		return (b);
	if (b < EPSILON)
		return (a);
	return (fmin(a, b));
}

t_real	closest_hit_dst_sol2(t_sol2 sol)
{
	if (sol.n == 0)
		return (-FLT_1);
	else if (sol.n == 1)
	{
		if (sol.r1 < EPSILON)
			return (-FLT_1);
		return (sol.r1);
	}
	else
		return (closest_hit_dst_dbl(sol.r1, sol.r2));
}
