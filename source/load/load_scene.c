/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:51:21 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 15:12:59 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static void	count_scene_from_file(t_app *app, const char *file)
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
