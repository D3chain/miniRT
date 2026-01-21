/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_material.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:26:42 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 17:14:14 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	setup_material(t_material *mat)
{
	mat->ka = DFL_KA;
	mat->kd = DFL_KD;
	mat->ks = DFL_KS;
	mat->shininess = DFL_SHINE;
	mat->ior = DFL_IOR;
}

static void	set_param(t_real *param, t_real value, t_real minimum)
{
	if (value <= minimum)
		*param = minimum;
	else
		*param = value;
}

static void	clamp_k_factors(t_material *mat)
{
	const t_real	k_sum = mat->ka + mat->kd + mat->ks;

	if (k_sum > FLT_1_1)
	{
		mat->ka /= k_sum;
		mat->kd /= k_sum;
		mat->ks /= k_sum;
	}
}

void	scan_material(t_app *app, const char *line, t_material *mat)
{
	const char	*param[] = {"k_amb", "k_dif", "k_spc", "shine", "ior__"};
	char		*scanned;
	t_real		param_value;
	int			i;

	setup_material(mat);
	i = -1;
	while (++i < N_MAT_FACTORS)
	{
		scanned = ft_strstr(line, param[i]);
		if (!scanned)
			continue ;
		scan_t_real(app, &param_value, scanned + LEN_FACTOR_NAME + 1);
		if (i == K_AMB)
			set_param(&mat->ka, param_value, MIN_KA);
		else if (i == K_DIF)
			set_param(&mat->kd, param_value, MIN_KD);
		else if (i == K_SPC)
			set_param(&mat->ks, param_value, MIN_KS);
		else if (i == shine)
			set_param(&mat->shininess, param_value, MIN_SHINE);
		else if (i == IOR__)
			set_param(&mat->ior, param_value, MIN_IOR);
	}
	clamp_k_factors(mat);
}
