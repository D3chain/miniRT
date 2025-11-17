/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:09:34 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 11:51:07 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	xopen(struct s_app *app, const char *file, int oflag)
{
	int	fd;

	fd = open(file, oflag);
	if (fd < 0)
	{
		app->status = errno;
		err_per(errno, "xopen");
	}
	return (fd);
}
