/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynome2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:14:57 by cgajean           #+#    #+#             */
/*   Updated: 2025/11/19 15:34:39 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

const t_sol2	polynome2(double a, double b, double c)
{
	const double		dis = pow(b, 2.0) - 4 * a * c;
	t_sol2				res;

	if (dis < 0)
	{
		res.n = 0;
	}
	else if (dis == 0)
	{
		res.n = 1;
		res.r1 = (-b) / (2 * a);
	}
	else
	{
		res.n = 2;
		res.r1 = (-b + sqrt(dis)) / (2 * a);
		res.r2 = (-b - sqrt(dis)) / (2 * a);
	}
	return (res);
}
