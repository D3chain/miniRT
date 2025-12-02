/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:09:34 by echatela          #+#    #+#             */
/*   Updated: 2025/12/02 11:49:41 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	xopen(struct s_app *app, const char *file, int oflag)
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
