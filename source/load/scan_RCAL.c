/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scan_RCAL.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:28:37 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/20 16:20:35 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	scan_R(struct s_app *app, const char *line, int _)
{
	(void) _;
	line += scan_int(app, &app->mlx.screen.resolution.x, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_int(app, &app->mlx.screen.resolution.y, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	if (*line)
		return (app->status = ERR_PARS);
	return (0);
}

int	scan_C(struct s_app *app, const char *line, int _)
{
	(void) _;
	line += scan_t_real3(app, &app->scene.camera.focal_center, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_t_real3(app, &app->scene.camera.dir, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_t_real(app, &app->scene.camera.fov, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	if (*line)
		return (app->status = ERR_PARS);
	return (0);
}

int	scan_A(struct s_app *app, const char *line, int _)
{
	(void) _;
	line += scan_t_real(app, &app->scene.ambient.ratio, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_color(app, &app->scene.ambient.color, line);
	ft_skipspaces(&line);
	if (app->status || *line)
		return (app->status = ERR_PARS);
	return (0);
}

int	scan_L(struct s_app *app, const char *line, int _)
{
	static int	light_index;
	
	(void) _;
	line += scan_t_real3(app, &app->scene.light[light_index].coord, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_t_real(app, &app->scene.light[light_index].ratio, line);
	if (app->status)
		return (app->status);
	ft_skipspaces(&line);
	line += scan_color(app, &app->scene.light[light_index].color, line);
	++light_index;
	ft_skipspaces(&line);
	if (app->status || *line)
		return (app->status = ERR_PARS);
	return (0);
}
