/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:51:21 by echatela          #+#    #+#             */
/*   Updated: 2025/12/16 16:34:30 by fox              ###   ########.fr       */
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

static int	scan_elem(struct s_app *app, const char *line)
{
	int					i;
	static int			i_elem;
	static const char	*l_elem[N_SCENE_ITEMS] = {"A", "C", "L", "pl", "sp", "cy"};
	static int			(*scan_fct[N_SCENE_ITEMS])(struct s_app *, const char *, int *) = {
		scan_A, scan_C, scan_L, scan_pl, scan_sp, scan_cy};

	i = 0;
	while (i < N_SCENE_ITEMS)
	{
		if (ft_strncmp(l_elem[i], line, ft_strlen(l_elem[i])) == 0)
		{
			scan_fct[i](app, next_tok(line), &i_elem);
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
