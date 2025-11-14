/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xopen.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:09:34 by echatela          #+#    #+#             */
/*   Updated: 2025/11/14 19:14:25 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	xopen(struct s_data *data, const char *file, int oflag)
{
	int	fd;

	fd = open(file, oflag);
	if (fd < 0)
	{
		data->status = errno;
		err_per(errno, "xopen");
	}
	return (fd);
}
