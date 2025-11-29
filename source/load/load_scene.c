/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:51:21 by echatela          #+#    #+#             */
/*   Updated: 2025/11/29 10:26:45 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


struct s_elem	create_sphere(t_double3 coord, double radius, t_color color)
{
	struct s_elem	elem;

	elem.type = SPHERE;
	elem.u.sphere.coord = coord;
	elem.u.sphere.radius = radius;
	elem.u.sphere.color = color;
	return (elem);
}

struct s_elem	create_plane(t_double3 coord, t_double3 normal, t_color color)
{
	struct s_elem	elem;

	elem.type = PLANE;
	elem.u.plane.coord = coord;
	elem.u.plane.normal = vector_normalise(normal);
	elem.u.plane.color = color;
	return (elem);
}

struct s_elem	create_cylinder(const t_double3 coord, const t_double3 axis,
	const double height, const double radius, const t_color color)
{
	struct s_elem	elem;

	elem.type = CYLINDER;
	elem.u.cylinder.coord = coord;
	elem.u.cylinder.axis = vector_normalise(axis);
	elem.u.cylinder.height = height;
	elem.u.cylinder.radius = radius;
	elem.u.cylinder.color = color;
	return (elem);
}

int	load_scene(struct s_app *app, char *file)
{
	(void) file;
	app->scene.camera.coord = (t_double3){0.0, 0.0, -100.0};
	app->scene.camera.dir = (t_double3){0.0, 0.0, 1.0};
	app->scene.camera.fov = 70;

	app->scene.light.coord = (t_double3){0.0, 500.0, 0.0};
	app->scene.light.ratio = 1.0;

	app->scene.n_elem = 2;
	app->scene.elems = xmalloc(app, sizeof(struct s_elem) * app->scene.n_elem);
	app->scene.elems[0] = create_cylinder((t_double3){0.0, 0.0, 0.0}, (t_double3){0.0, 1.0, 0.5}, 150, 50, color_int(RED));
	app->scene.elems[1] = create_sphere((t_double3){0.0, 0.0, 0.0}, 70, color_int(GREEN));
	// app->scene.elems[2] = create_plane((t_double3){0.0, 0.0, 0.0}, (t_double3){1.0, 0.0, -0.3}, color_int(BLACK));
	return (app->status);
}










int	ft_isspace_str(const char *str)
{
	while (*str)
	{
		if (!ft_isspace(*str))
			return (0);
		str++;
	}
	return (1);
}

int	count_elems_from_file(struct s_app *app, const char *file)
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
		if (ft_isspace_str(line))
			n_elem++;
		free(line);
		line = gets_next_line(fd);
	}
	return (n_elem);
}

int	check_set_elems_from_file(struct s_app *app, const char *file)
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
		if (check_set_elem(app, line) != 0)
			return (free(line), app->status);
		free(line);
		line = gets_next_line(fd);
	}
	close(fd);
	return (0);
}

int	load_scene(struct s_app *app, const char *file)
{
	char		*line;
	int			n_elem;

	n_elem = count_elems_from_file(app, file);
	if (app->status)
		return (app->status);
	app->scene.n_elem = n_elem;
	if (check_set_elems_from_file(app, file));
		return (app->status);
	return (0);
}
