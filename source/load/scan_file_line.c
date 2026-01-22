/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_file_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 12:46:45 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/22 18:22:22 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef int	(*t_scan_fn_tbl[N_SCENE_ITEMS])(t_app *, const char *, int);
typedef int	(*t_scan_fn)(t_app *, const char *, int);

static char	*next_tok(const char *str)
{
	while (*str && !ft_isspace(*str))
		str++;
	while (*str && ft_isspace(*str))
		str++;
	return ((char *)str);
}

t_scan_fn	get_scan_fn(int index)
{
	static t_scan_fn_tbl	tbl = {\
		scan_r, scan_a, scan_c, scan_l, scan_pl, scan_sp, scan_cy, scan_co};

	return (tbl[index]);
}

static int	find_type(const char *line, int type_idx)
{
	static const char	*types[N_SCENE_ITEMS] = {\
		"R", "A", "C", "L", "pl", "sp", "cy", "co"};

	return (!ft_strncmp(types[type_idx], line, ft_strlen(types[type_idx])));
}

static void
	select_shape_list(t_scene *scene, int itered_i, int *shape_i, \
														t_shape **shape_tbl)
{
	static int	i_elem;
	static int	i_elem_inf;

	if (itered_i == N_SETUP_ITEMS)
	{
		*shape_tbl = scene->elems_inf;
		*shape_i = i_elem_inf++;
	}
	else if (itered_i > N_SETUP_ITEMS)
	{
		*shape_i = i_elem++;
		*shape_tbl = scene->elems;
	}
}

int	scan_file_line(t_app *app, const char *line)
{
	t_shape		*shape_tbl;
	int			shape_i;
	int			i;

	i = -1;
	while (++i < N_SCENE_ITEMS)
	{
		if (find_type(line, i))
		{
			select_shape_list(&app->scene, i, &shape_i, &shape_tbl);
			(get_scan_fn(i))(app, next_tok(line), shape_i);
			if (app->status)
				return (app->status);
			if (i >= N_SETUP_ITEMS)
				scan_material(app, line, \
							&shape_tbl[(shape_i)].u_.any.material);
			break ;
		}
	}
	return (app->status = (ERR_PARS * (i == N_SCENE_ITEMS)));
}
