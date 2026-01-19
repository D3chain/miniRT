/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:26:42 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/19 18:06:44 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_param(t_real *param, t_real value, t_real minimum)
{
	if (value <= minimum)
		*param = minimum;
	else
		*param = value;
}

void	scan_material(struct s_app *app, const char *line, t_material *mat)
{
	static const char	*param[] = MAT_FACTORS;
	char				*scanned;
	t_real				param_value;
	int					param_rank;
	int					i;

	i = -1;
	while (++i < N_MAT_FACTORS)
	{
		scanned = ft_strstr(line, param[i]);
		if (scanned)
			scan_t_real(app, &param_value, scanned + LEN_FACTOR_NAME + 1);
		else
			param_value = FLT_0;
		if (i == K_AMB)
			set_param(&mat->ka, param_value, MIN_NORM_VALUE);
		else if (i == K_DIF)
			set_param(&mat->kd, param_value, MIN_NORM_VALUE);
		else if (i == K_SPC)
			set_param(&mat->ks, param_value, MIN_NORM_VALUE);
		else if (i == SHI__)
			set_param(&mat->shininess, param_value, MIN_SHI_VALUE);
		else if (i == IOR__)
			set_param(&mat->ior, param_rank, MIN_NORM_VALUE);
	}
}
