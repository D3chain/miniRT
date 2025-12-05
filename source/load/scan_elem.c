/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_elem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 10:25:22 by echatela          #+#    #+#             */
/*   Updated: 2025/12/02 11:34:53 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_A(struct s_app *app, const char *line, int *_)
{
	line += scan_double(app, &app->scene.ambient_light.ratio, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_color(app, &app->scene.ambient_light.color, line);
	ft_skipspaces(&line);
	if (app->status || *line)
		return (app->status = ERR_PARS);
	return (0);
}

int	parse_C(struct s_app *app, const char *line, int *_)
{
	line += scan_double3(app, &app->scene.camera.focal_center, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_double3(app, &app->scene.camera.dir, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_double(app, &app->scene.camera.fov, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	if (*line)
		return (app->status = ERR_PARS);
	return (0);
}

int	parse_L(struct s_app *app, const char *line, int *_)
{
	line += scan_double3(app, &app->scene.light.coord, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_double(app, &app->scene.light.ratio, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_color(app, &app->scene.light.color, line);
	ft_skipspaces(&line);
	if (app->status || *line)
		return (app->status = ERR_PARS);
	return (0);
}

int	parse_pl(struct s_app *app, const char *line, int *i_elem)
{
	app->scene.elems[*i_elem].type = PLANE;
	line += scan_double3(app, &app->scene.elems[*i_elem].u.plane.coord, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_double3(app, &app->scene.elems[*i_elem].u.plane.normal, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_color(app, &app->scene.elems[*i_elem].u.plane.color, line);
	ft_skipspaces(&line);
	if (app->status || *line)
		return (app->status = ERR_PARS);
	return (0);
}

int	parse_sp(struct s_app *app, const char *line, int *i_elem)
{
	app->scene.elems[*i_elem].type = SPHERE;
	line += scan_double3(app, &app->scene.elems[*i_elem].u.sphere.coord, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_double(app, &app->scene.elems[*i_elem].u.sphere.radius, line);
	if (app->status)
		return (app->status);
	app->scene.elems[*i_elem].u.sphere.radius /= 2;
	ft_skipspaces(&line);
	line += scan_color(app, &app->scene.elems[*i_elem].u.sphere.color, line);
	ft_skipspaces(&line);
	if (app->status || *line)
		return (app->status = ERR_PARS);
	return (0);
}

int	parse_cy(struct s_app *app, const char *line, int *i_elem)
{
	app->scene.elems[*i_elem].type = CYLINDER;
	line += scan_double3(app, &app->scene.elems[*i_elem].u.cylinder.coord, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_double3(app, &app->scene.elems[*i_elem].u.cylinder.axis, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_double(app, &app->scene.elems[*i_elem].u.cylinder.radius, line);
	if (app->status)
		return (app->status);
	app->scene.elems[*i_elem].u.cylinder.radius /= 2;
	ft_skipspaces(&line);
	line += scan_double(app, &app->scene.elems[*i_elem].u.cylinder.height, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_color(app, &app->scene.elems[*i_elem].u.cylinder.color, line);
	ft_skipspaces(&line);
	if (app->status || *line)
		return (app->status = ERR_PARS);
	return (0);
}

int	scan_elem(struct s_app *app, const char *line)
{
	int					i;
	static int			i_elem;
	static const char	*l_elem[N_SCENE_ITEMS] = {"A", "C", "L", "pl", "sp", "cy"};
	static int			(*parse_fct[N_SCENE_ITEMS])(struct s_app *, const char *, int *) = {
		parse_A, parse_C, parse_L, parse_pl, parse_sp, parse_cy};

	i = 0;
	while (i < N_SCENE_ITEMS)
	{
		if (ft_strncmp(l_elem[i], line, ft_strlen(l_elem[i])) == 0)
		{
			parse_fct[i](app, next_tok(line), &i_elem);
			if (i > 2)
				i_elem++;
			break ;
		}
		++i;
	}
	if (i == N_SCENE_ITEMS)
		app->status = ERR_PARS;
	return (app->status);
}
