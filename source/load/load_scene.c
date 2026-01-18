/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:51:21 by echatela          #+#    #+#             */
/*   Updated: 2026/01/17 20:59:15 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	count_scene_from_file(struct s_app *app, const char *file)
{
	int		fd;
	char	*line;

	fd = xopen(app, file, O_RDONLY);
	if (app->status)
		return ;
	line = gets_next_line(fd);
	while (line)
	{
		if (!ft_isspace_str(line) && *line != '#')
		{
			if (*line == 'L')
				++app->scene.n_light;
			else if (ft_islower(*line))
			{
				if (!ft_strncmp(line, "pl", 2))
					++app->scene.n_elem_inf;
				else
					++app->scene.n_elem;
			}
		}
		free(line);
		line = gets_next_line(fd);
	}
	close(fd);
}

static int	scan_file(struct s_app *app, const char *line)
{
	int					i;
	static int			i_elem;
	static const char	*l_elem[N_SCENE_ITEMS] = {"R", "A", "C", "L", "pl", "sp", "cy", "co"};
	static int			(*scan_fct[N_SCENE_ITEMS])(struct s_app *, const char *, int *) = {
		scan_R, scan_A, scan_C, scan_L, scan_pl, scan_sp, scan_cy, scan_co};

	i = 0;
	while (i < N_SCENE_ITEMS)
	{
		if (ft_strncmp(l_elem[i], line, ft_strlen(l_elem[i])) == 0)
		{
			scan_fct[i](app, next_tok(line), &i_elem);
			if (i > N_SETUP_ITEMS)
				++i_elem;
			break ;
		}
		++i;
	}
	if (i == N_SCENE_ITEMS)
		app->status = ERR_PARS;
	return (app->status);
}

static int	scan_scene_from_file(struct s_app *app, const char *file)
{
	int		fd;
	char	*line;

	app->scene.elems = xmalloc(app, sizeof(struct s_elem) * app->scene.n_elem);
	app->scene.elems_inf = xmalloc(app, sizeof(struct s_elem) * app->scene.n_elem_inf);
	app->scene.light = xmalloc(app, sizeof(struct s_light) * app->scene.n_light);
	if (app->status)
		return (app->status);
	fd = xopen(app, file, O_RDONLY);
	if (app->status)
		return (app->status);
	line = gets_next_line(fd);
	while (line)
	{
		if (!ft_isspace_str(line) && *line != '#' && scan_file(app, line) != 0)
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

	count_scene_from_file(app, file);
	if (app->status)
		return (app->status);
	if (scan_scene_from_file(app, file))
		return (app->status);
	setup_shapes(app, &app->scene);
	setup_RCAL(app);
	bvh_build(app, &app->scene);
	return (0);
}
