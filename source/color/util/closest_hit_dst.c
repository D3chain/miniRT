/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_hit_dst.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:02:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/11/19 16:25:59 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	closest_hit_dst_dbl(const double a, const double b)
{
	if (a <= 0 && b > 0)
		return (b);
	else if (b <= 0 && a > 0)
		return (a);
	else
		return (fmin(a, b));
}

double	closest_hit_dst_sol2(t_sol2 sol)
{
	if (sol.n == 0)
		return (-1.0);
	else if (sol.n == 1)
		return (sol.r1);
	else
		return (closest_hit_dst_dbl(sol.r1, sol.r2));
}
