/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:51:21 by echatela          #+#    #+#             */
/*   Updated: 2025/12/03 12:50:44 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


// struct s_elem	create_sphere(t_double3 coord, double radius, t_color color)
// {
// 	struct s_elem	elem;

// 	elem.type = SPHERE;
// 	elem.u.sphere.coord = coord;
// 	elem.u.sphere.radius = radius;
// 	elem.u.sphere.color = color;
// 	return (elem);
// }

// struct s_elem	create_plane(t_double3 coord, t_double3 normal, t_color color)
// {
// 	struct s_elem	elem;

// 	elem.type = PLANE;
// 	elem.u.plane.coord = coord;
// 	elem.u.plane.normal = vector_normalise(normal);
// 	elem.u.plane.color = color;
// 	return (elem);
// }

// struct s_elem	create_cylinder(const t_double3 coord, const t_double3 axis,
// 	const double height, const double radius, const t_color color)
// {
// 	struct s_elem	elem;

// 	elem.type = CYLINDER;
// 	elem.u.cylinder.coord = coord;
// 	elem.u.cylinder.axis = vector_normalise(axis);
// 	elem.u.cylinder.height = height;
// 	elem.u.cylinder.radius = radius;
// 	elem.u.cylinder.color = color;
// 	return (elem);
// }

// void	init_cam(struct s_camera *cam)
// {
// 	cam->camera_center = (t_double3){0.0, 0.0, -500.0};
// 	cam->dir = (t_double3){0.0, 0.0, 1.0};
// 	cam->focal_length = FOCAL_LENGTH;
// 	cam->viewport_height = 2 * tan(ft_toradian(FOV) / 2) * FOCAL_LENGTH;
// 	cam->viewport_width = cam->viewport_height * IMG_RATIO;
// 	cam->viewport_u = (t_double3){cam->viewport_width, 0.0, 0.0};
// 	cam->viewport_v = (t_double3){0.0, cam->viewport_height, 0.0};
// 	// cam->viewport_upper_left = minus3(cam->camera_center, 
// }

// int	load_scene(struct s_app *app, char *file)
// {
// 	(void) file;
// 	init_cam(&app->scene.camera);
// 	app->scene.camera.camera_center = (t_double3){0.0, 0.0, -100.0};
// 	app->scene.camera.dir = (t_double3){0.0, 0.0, 1.0};
// 	app->scene.camera.fov = 70;

// 	app->scene.light.coord = (t_double3){0.0, 500.0, 0.0};
// 	app->scene.light.ratio = 1.0;

// 	app->scene.n_elem = 2;
// 	app->scene.elems = xmalloc(app, sizeof(struct s_elem) * app->scene.n_elem);
// 	app->scene.elems[0] = create_cylinder((t_double3){0.0, 0.0, 0.0}, (t_double3){0.0, 1.0, 0.5}, 150, 50, color_int(RED));
// 	app->scene.elems[1] = create_sphere((t_double3){0.0, 0.0, 0.0}, 70, color_int(GREEN));
// 	// app->scene.elems[2] = create_plane((t_double3){0.0, 0.0, 0.0}, (t_double3){1.0, 0.0, -0.3}, color_int(BLACK));
// 	return (app->status);
// }










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
		if (!ft_isspace_str(line) && ft_islower(*line) && *line != '#')
			n_elem++;
		free(line);
		line = gets_next_line(fd);
	}
	return (n_elem);
}

int	scan_elems_from_file(struct s_app *app, const char *file)
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
	// for (int i = 0; i < app->scene.n_elem; i++) {
	// 	printf("%d\n", app->scene.elems[i].type);
	// }
	printf("rad: %f\n", app->scene.elems[0].u.sphere.coord.x);
	
	return (0);
}
