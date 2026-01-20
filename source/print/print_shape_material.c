/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_shape_material.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 15:37:44 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 15:46:44 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_shape_material(int fd, t_material *m)
{
	static const char	*factors[] = MAT_FACTORS;
	const t_real 		values[] = {m->ka, m->kd, m->ks, m->shininess, m->ior};
	int					i;

	i= -1;
	while (++i < N_MAT_FACTORS)
		dprintf(fd, "\t%s="REAL, factors[i], values[i]);
}
