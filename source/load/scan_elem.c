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

int	scan_pl(struct s_app *app, const char *line, int *i_elem)
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
	line += scan_color(app, &app->scene.elems[*i_elem].u.plane.material.color, line);
	ft_skipspaces(&line);
	if (app->status || *line)
		return (app->status = ERR_PARS);
	return (0);
}

int	scan_sp(struct s_app *app, const char *line, int *i_elem)
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
	line += scan_color(app, &app->scene.elems[*i_elem].u.sphere.material.color, line);
	ft_skipspaces(&line);
	if (app->status || *line)
		return (app->status = ERR_PARS);
	return (0);
}

int	scan_cy(struct s_app *app, const char *line, int *i_elem)
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
	line += scan_color(app, &app->scene.elems[*i_elem].u.cylinder.material.color, line);
	ft_skipspaces(&line);
	if (app->status || *line)
		return (app->status = ERR_PARS);			
	return (0);
}
