/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynome2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:14:57 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 19:14:13 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

__attribute__((pure))
t_sol2	polynome2(t_real a, t_real b, t_real c)
{
	const t_real		dis = b * b - FLT_4 * a * c;
	t_sol2				res;

	res.n = FLT_0;
	res.r1 = FLT_0;
	res.r2 = FLT_0;
	if (dis < FLT_0)
		res.n = 0;
	else if (dis == 0)
	{
		res.n = 1;
		res.r1 = (-b) / (FLT_2 * a);
	}
	else
	{
		res.n = 2;
		res.r1 = (-b - sqrt(dis)) / (FLT_2 * a);
		res.r2 = (-b + sqrt(dis)) / (FLT_2 * a);
	}
	return (res);
}
