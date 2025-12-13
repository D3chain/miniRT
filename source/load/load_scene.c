/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:51:21 by echatela          #+#    #+#             */
/*   Updated: 2025/12/13 17:29:31 by echatela         ###   ########.fr       */
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

void	complete_A(struct s_app *app, struct s_ambient *ambient)
{
	if (ambient->ratio > 1.0)
		ambient->ratio = 1.0;
	if (ambient->ratio < 0.0)
		ambient->ratio = 0.0;
}

void	complete_C(struct s_app *app, struct s_camera *camera)
{
	camera->focal_length = FOCAL_LENGTH;
	camera->fov_rad = ft_toradian(camera->fov);
	camera->viewport_height = 2.0 * tan(camera->fov_rad / 2.0) * camera->focal_length;
	camera->viewport_width = camera->viewport_height * IMG_RATIO;
	if (camera->dir.y > 0.99 || camera->dir.y < -0.99)
		camera->viewport_u = (t_double3){1.0, 0.0, 0.0};
	else
		camera->viewport_u = mul3(normalize3(cross3(camera->dir, (t_double3){0.0, -1.0, 0.0})), camera->viewport_width);
	camera->viewport_u_px = mul3(camera->viewport_u, 1.0 / WIN_WIDTH);
	camera->viewport_v = mul3(normalize3(cross3(camera->dir, camera->viewport_u)), -camera->viewport_height);
	camera->viewport_v_px = mul3(camera->viewport_v, 1.0 / WIN_HEIGHT);
	camera->viewport_upper_left = minus3(plus3(camera->focal_center, camera->dir), plus3(mul3(camera->viewport_u, 0.5), mul3(camera->viewport_v, 0.5)));
	camera->pixel00_loc = plus3(plus3(camera->viewport_upper_left, mul3(camera->viewport_u_px, 0.5)),
			mul3(camera->viewport_v_px, 0.5));
}

void	complete_L(struct s_app *app, struct s_light *light)
{
	if (light->ratio > 1.0)
		light->ratio = 1.0;
	if (light->ratio < 0.0)
		light->ratio = 0.0;
}

void	complete_pl(struct s_app *app, struct s_elem *elem)
{
	struct s_plane	*plane;

	plane = &elem->u.plane;
	plane->normal = normalize3(plane->normal);
}

void	complete_sp(struct s_app *app, struct s_elem *elem)
{
	struct s_sphere	*sphere;

	sphere = &elem->u.sphere;
	sphere->radius_sq = sphere->radius * sphere->radius;
}

void	complete_cy(struct s_app *app, struct s_elem *elem)
{
	struct s_cylinder	*cylinder;

	cylinder = &elem->u.cylinder;
	cylinder->radius_sq = cylinder->radius * cylinder->radius;
	cylinder->axis = normalize3(cylinder->axis);
}

static void	complete_scene(struct s_app *app, struct s_scene *scene)
{
	static void	(*complete_fct[N_SCENE_ELEMS])(struct s_app *, struct s_elem *) = {
		complete_pl, complete_sp, complete_cy};
	int	i;

	complete_C(app, &scene->camera);
	complete_A(app, &scene->ambient);
	complete_L(app, &scene->light);
	i = -1;
	while (++i < scene->n_elem)
		complete_fct[scene->elems[i].type](app, &scene->elems[i]);
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
	complete_scene(app, &app->scene);
	return (0);
}
