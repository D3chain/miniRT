/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:51:21 by echatela          #+#    #+#             */
/*   Updated: 2026/01/23 12:13:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

enum e_scene_flags
{
	IS_RES = 227,
	IS_CAM = 1091,
	IS_AMB = 11171,
};

static int	scan_scene_from_file(t_app *app, const char *file)
{
	int		fd;
	char	*line;

	app->scene.elems = \
		xmalloc(app, sizeof(struct s_shape) * app->scene.n_elem);
	app->scene.elems_inf = \
		xmalloc(app, sizeof(struct s_shape) * app->scene.n_elem_inf);
	app->scene.light = \
		xmalloc(app, sizeof(t_light) * app->scene.n_light);
	if (app->status)
		return (app->status);
	fd = xopen(app, file, O_RDONLY);
	if (app->status)
		return (app->status);
	line = gets_next_line(fd);
	while (line)
	{
		if (!ft_isspace_str(line) && *line != '#' \
			&& scan_file_line(app, line) != 0)
			return (close(fd), free(line), app->status);
		free(line);
		line = gets_next_line(fd);
	}
	return (close(fd), ERR_NONE);
}

static bool	is_format_ok(t_app *app, const char *line, int offset)
{
	if (ft_isspace(*(line + offset)))
		return (true);
	else
	{
		app->status = ERR_PARS;
		return (false);
	}
}

static void
	count_by_elem(t_app *app, const char *line, int *res_flag, int *setup_flag)
{
	if (*line == 'R')
		return ((void)(*res_flag += IS_RES * is_format_ok(app, line, 1)));
	if (*line == 'C')
		return ((void)(*setup_flag += IS_CAM * is_format_ok(app, line, 1)));
	else if (*line == 'A')
		return ((void)(*setup_flag += IS_AMB * is_format_ok(app, line, 1)));
	if (*line == 'L')
		return ((void)(++app->scene.n_light * is_format_ok(app, line, 1)));
	if (!ft_isupper(*line) && is_format_ok(app, line, 2))
	{
		if (!ft_strncmp(line, "pl", 2))
			++app->scene.n_elem_inf;
		else
			++app->scene.n_elem;
	}
	else
		app->status = ERR_PARS;
}

static void	count_scene_from_file(t_app *app, const char *file)
{
	int			fd;
	char		*line;
	static int	resolution_flag;
	static int	setup_flag;

	fd = xopen(app, file, O_RDONLY);
	if (app->status)
		return ;
	line = gets_next_line(fd);
	while (line)
	{
		if (*line != '#' && !ft_isspace_str(line))
			count_by_elem(app, line, &resolution_flag, &setup_flag);
		free(line);
		if (app->status)
			break ;
		line = gets_next_line(fd);
	}
	close(fd);
	if (!app->status)
		app->status = ERR_PARS * ((resolution_flag > IS_RES) \
								|| (setup_flag != IS_CAM + IS_AMB) \
								|| (app->scene.n_elem + app->scene.n_elem_inf) <= 0);
}

int	load_scene(t_app *app)
{
	count_scene_from_file(app, app->file_name);
	if (app->status)
		return (app->status);
	if (scan_scene_from_file(app, app->file_name))
		return (app->status);
	setup_rcal(app);
	setup_shapes(app, &app->scene);
	bvh_build(app, &app->scene);
	return (ERR_NONE);
}
