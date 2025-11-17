/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:27:39 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 11:50:57 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* fake functions for compilation */

int	parse_file(struct s_app *app, int fd)
{
	(void) app;
	(void) fd;
	return (0);
}

/*****/


int init_scene(struct s_app *app, const char *file)
{
	int	fd;

	fd = xopen(app, file, O_RDONLY);
	if (fd < 0)
		return (1);
	if (parse_file(app, fd))
		return (1);
	return (0);
}
