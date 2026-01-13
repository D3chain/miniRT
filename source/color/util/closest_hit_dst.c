/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit_dst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:02:24 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/13 16:48:26 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_real	closest_hit_dst_dbl(const t_real a, const t_real b)
{
	if (a <= 0 && b > 0)
		return (b);
	else if (b <= 0 && a > 0)
		return (a);
	else
		return (fmin(a, b));
}

t_real	closest_hit_dst_sol2(t_sol2 sol)
{
	if (sol.n == 0)
		return (-1.0);
	else if (sol.n == 1)
		return (sol.r1);
	else
		return (closest_hit_dst_dbl(sol.r1, sol.r2));
}
