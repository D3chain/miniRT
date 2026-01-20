/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:20:52 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 16:41:47 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	scan_pl(struct s_app *app, const char *line, int i_elem)
{
	struct s_plane	*p;
	
	p = &app->scene.elems_inf[i_elem].u.plane;
	app->scene.elems_inf[i_elem].type = PLANE;
	line += scan_t_real3(app, &p->coord, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_t_real3(app, &p->normal, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_color(app, &p->material.color, line);
	ft_skipspaces(&line);
	return (app->status);
}

int	scan_sp(struct s_app *app, const char *line, int i_elem)
{
	struct s_sphere	*s;
	
	s = &app->scene.elems[i_elem].u.sphere;
	app->scene.elems[i_elem].type = SPHERE;
	line += scan_t_real3(app, &s->coord, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_t_real(app, &s->radius, line);
	if (app->status)
		return (app->status);
	s->radius /= 2;
	ft_skipspaces(&line);
	line += scan_color(app, &s->material.color, line);
	ft_skipspaces(&line);
	return (app->status);
}

int	scan_cy(struct s_app *app, const char *line, int i_elem)
{
	struct s_cylinder	*c;

	c = &app->scene.elems[i_elem].u.cylinder;
	app->scene.elems[i_elem].type = CYLINDER;
	line += scan_t_real3(app, &c->coord, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_t_real3(app, &c->axis, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_t_real(app, &c->radius, line);
	if (app->status)
		return (app->status);
	app->scene.elems[i_elem].u.cylinder.radius /= 2;
	ft_skipspaces(&line);
	line += scan_t_real(app, &c->height, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_color(app, &c->material.color, line);
	ft_skipspaces(&line);
	return (app->status);
}

int	scan_co(struct s_app *app, const char *line, int i_elem)
{
	struct s_cone	*c;

	c = &app->scene.elems[i_elem].u.cone;
	app->scene.elems[i_elem].type = CONE;
	line += scan_t_real3(app, &c->coord, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_t_real3(app, &c->axis, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_t_real(app, &c->radius, line);
	if (app->status)
		return (app->status);
	c->radius /= 2;
	ft_skipspaces(&line);
	line += scan_t_real(app, &c->height, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_color(app, &c->material.color, line);
	ft_skipspaces(&line);
	return (app->status);
}
