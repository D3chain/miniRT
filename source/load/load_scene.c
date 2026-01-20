/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:51:21 by echatela          #+#    #+#             */
/*   Updated: 2026/01/20 16:53:56 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_elem_iter
{
	int				i;
	int				*cur_i;
	int				i_elem;
	int				i_elem_inf;
	struct s_elem	*tab;
} t_elem_iter;

static char	*next_tok(const char *str)
{
	while (*str && !ft_isspace(*str))
		str++;
	while (*str && ft_isspace(*str))
		str++;
	return ((char *)str);
}

static void	count_scene_from_file(struct s_app *app, const char *file)
{
	int		fd;
	char	*line;

	fd = xopen(app, file, O_RDONLY);
	if (app->status)
		return ;
	line = gets_next_line(fd);
	while (line)
	{
		if (!ft_isspace_str(line) && *line != '#')
		{
			if (*line == 'L')
				++app->scene.n_light;
			else if (ft_islower(*line))
			{
				if (!ft_strncmp(line, "pl", 2))
					++app->scene.n_elem_inf;
				else
					++app->scene.n_elem;
			}
		}
		free(line);
		line = gets_next_line(fd);
	}
	close(fd);
}

static int	scan_file(struct s_app *app, const char *line)
{
	static scan_fn		sfn = {scan_R, scan_A, scan_C, \
							scan_L, scan_pl, scan_sp, scan_cy, scan_co};
	static const char	*l_elem[N_SCENE_ITEMS] = SCENE_ITEMS;
	static t_elem_iter	it;

	it.i = -1;
	while (++it.i < N_SCENE_ITEMS)
		if (ft_strncmp(l_elem[it.i], line, ft_strlen(l_elem[it.i])) == 0)
		{
			it.cur_i = &it.i_elem;
			it.tab = app->scene.elems;
			if (it.i == N_SETUP_ITEMS)	
			{
				it.tab = app->scene.elems_inf;
				it.cur_i = &it.i_elem_inf;
			}
			sfn[it.i](app, next_tok(line), *it.cur_i);
			if (app->status)
				return (app->status);
			if (it.i >= N_SETUP_ITEMS)
				scan_material(app, line, &it.tab[(*it.cur_i)++].u.any.material);
			break ;
		}
	return (app->status = (ERR_PARS * (it.i == N_SCENE_ITEMS)));
}

static int	scan_scene_from_file(struct s_app *app, const char *file)
{
	int		fd;
	char	*line;

	app->scene.elems = \
		xmalloc(app, sizeof(struct s_elem) * app->scene.n_elem);
	app->scene.elems_inf = \
		xmalloc(app, sizeof(struct s_elem) * app->scene.n_elem_inf);
	app->scene.light = \
		xmalloc(app, sizeof(struct s_light) * app->scene.n_light);
	if (app->status)
		return (app->status);
	fd = xopen(app, file, O_RDONLY);
	if (app->status)
		return (app->status);
	line = gets_next_line(fd);
	while (line)
	{
		if (!ft_isspace_str(line) && *line != '#' && scan_file(app, line) != 0)
			return (close(fd), free(line), app->status);
		free(line);
		line = gets_next_line(fd);
	}
	return (close(fd), ERR_NONE);
}

int	load_scene(struct s_app *app)
{
	char		*line;
	int			n_elem;

	count_scene_from_file(app, app->file_name);
	if (app->status)
		return (app->status);
	if (scan_scene_from_file(app, app->file_name))
		return (app->status);
	setup_RCAL(app);
	setup_shapes(app, &app->scene);
	bvh_build(app, &app->scene);
	return (ERR_NONE);
}
