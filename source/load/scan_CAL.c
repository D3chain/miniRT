/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_CAL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:28:37 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/15 15:33:21 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	scan_C(struct s_app *app, const char *line, int *_)
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

int	scan_A(struct s_app *app, const char *line, int *_)
{
	line += scan_double(app, &app->scene.ambient.ratio, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_color(app, &app->scene.ambient.color, line);
	ft_skipspaces(&line);
	if (app->status || *line)
		return (app->status = ERR_PARS);
	return (0);
}

int	scan_L(struct s_app *app, const char *line, int *_)
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
