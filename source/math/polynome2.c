/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   polynome2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:14:57 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/08 17:17:04 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ATTENTION IL FAUT MODIFIER CELA POUR QU'IL RETURN UN DOUBLE ET NON UN TRUC COMME CA
t_sol2	polynome2(double a, double b, double c)
{
	const double		dis = b * b - 4 * a * c;
	t_sol2				res;

	ft_bzero(&res, sizeof(res));
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
		// if (ft_dblcmp(res.r1, 0.0, EPSILON) < 0.0)
			res.r2 = (-b + sqrt(dis)) / (2 * a);
		// else
			// res.r2 = -1.0;
	}
	return (res);
}
