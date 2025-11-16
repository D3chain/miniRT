/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:27:39 by echatela          #+#    #+#             */
/*   Updated: 2025/11/16 17:29:17 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* fake functions for compilation */

int	parse_file(struct s_data *data, int fd)
{
	(void) data;
	(void) fd;
	return (0);
}

/*****/


bool init_scene(struct s_data *data, const char *file)
{
	int	fd;

	fd = xopen(data, file, O_RDONLY);
	if (fd < 0)
		return (1);
	if (parse_file(data, fd))
		return (1);
	return (0);
}
