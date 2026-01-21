/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:09:34 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 11:45:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	xopen(t_app *app, const char *file, int oflag)
{
	int	fd;

	fd = open(file, oflag);
	if (fd < 0)
	{
		app->status = ERR_SYS;
		err_per(app->status, "xopen");
	}
	return (fd);
}
