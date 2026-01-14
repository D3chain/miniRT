/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynome2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:14:57 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/14 13:06:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((pure))
t_sol2	polynome2(t_real a, t_real b, t_real c)
{
	const t_real		dis = b * b - 4 * a * c;
	t_sol2				res;

	res.n = 0.0;
	res.r1 = 0.0;
	res.r2 = 0.0;
	if (dis < 0)
		res.n = 0;
	else if (dis == 0)
	{
		res.n = 1;
		res.r1 = (-b) / (2 * a);
	}
	else
	{
		res.n = 2;
		res.r1 = (-b - sqrt(dis)) / (2 * a);
		res.r2 = (-b + sqrt(dis)) / (2 * a);
	}
	return (res);
}
