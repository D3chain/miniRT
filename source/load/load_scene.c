/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:51:21 by echatela          #+#    #+#             */
/*   Updated: 2025/12/04 15:19:45 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	count_elems_from_file(struct s_app *app, const char *file)
{
	int		fd;
	char	*line;
	int		n_elem;

	fd = xopen(app, file, O_RDONLY);
	if (app->status)
		return (app->status);
	n_elem = 0;
	line = gets_next_line(fd);
	while (line)
	{
		if (!ft_isspace_str(line) && ft_islower(*line) && *line != '#')
			n_elem++;
		free(line);
		line = gets_next_line(fd);
	}
	return (n_elem);
}

static int	scan_elems_from_file(struct s_app *app, const char *file)
{
	int		fd;
	char	*line;

	app->scene.elems = xmalloc(app, sizeof(struct s_elem) * app->scene.n_elem);
	if (app->status)
		return (app->status);
	fd = xopen(app, file, O_RDONLY);
	if (app->status)
		return (app->status);
	line = gets_next_line(fd);
	while (line)
	{
		if (!ft_isspace_str(line) && *line != '#' && scan_elem(app, line) != 0)
			return (close(fd), free(line), app->status);
		free(line);
		line = gets_next_line(fd);
	}
	close(fd);
	return (0);
}

static void	set_camera_parameters(struct s_app *app, struct s_camera *camera)
{
	const double	theta = ft_toradian(camera->fov);
	const double	w = tan(theta / 2);
	
	camera->focal_center = minus3(camera->viewport_center, mul3(camera->dir, -1.0));
	camera->focal_length = FOCAL_LENGTH;
	camera->viewport_width = 2 * w * camera->focal_length;
	camera->viewport_height = camera->viewport_width * IMG_RATIO;
	camera->viewport_u = cross3(camera->dir, (t_double3){camera->dir.x, 0.0, camera->dir.z});
	camera->viewport_v = cross3(camera->dir, camera->viewport_u);
	camera->viewport_upper_left;
	camera->pixel00_loc;
}

int	load_scene(struct s_app *app, const char *file)
{
	char		*line;
	int			n_elem;

	n_elem = count_elems_from_file(app, file);
	if (app->status)
		return (app->status);
	app->scene.n_elem = n_elem;
	if (scan_elems_from_file(app, file))
		return (app->status);
	set_camera_parameters(app, &app->scene.camera);
	return (0);
}
