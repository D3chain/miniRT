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

int	parse_A(struct s_app *app, const char *line);

int	parse_C(struct s_app *app, const char *line)
{
	char	*cur_tok;

	app->scene.camera.viewport_center = scan_double3(app, next_tok(&cur_tok));
	if (app->status)
		return (app->status);
	app->scene.camera.dir = scan_double3(app, next_tok(&cur_tok));
	if (app->status)
		return (app->status);
	app->scene.camera.fov = scan_int(app, next_tok(&cur_tok));
	if (next_tok(&cur_tok))
		return (app->status = ERR_PARS);
	return (0);
}

int	parse_L(struct s_app *app, const char *line);
int	parse_pl(struct s_app *app, const char *line);
int	parse_sp(struct s_app *app, const char *line); 
int	parse_cy(struct s_app *app, const char *line);

int	scan_elem(struct s_app *app, const char *line)
{
	int					i;
	static const char	*l_elem[N_SCENE_ITEMS] = {"A", "C", "L", "pl", "sp", "cy"};
	static const int	(*parse_fct[N_SCENE_ITEMS])(struct s_app *, const char *) = {
		parse_A, parse_C, parse_L, parse_pl, parse_sp, parse_cy};

	i = 0;
	while (i < N_SCENE_ITEMS)
	{
		if (ft_strncmp(l_elem[i], line, ft_strlen(l_elem[i])) == 0)
		{
			parse_fct[i](app, line);
			break ;
		}
		++i;
	}
	if (i == N_SCENE_ITEMS)
		app->status = ERR_PARS;
	return (app->status);
}
