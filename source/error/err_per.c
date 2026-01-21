/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_per.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:05:34 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 14:14:23 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/* 	char	err_buf[BUFSIZ];
	int		i;

	if (ft_strlen(ctx) + ft_strlen(strerror(errno)) + 14 > BUFSIZ - 1)
		write(2, "miniRT: \n", 19);
	i = 0;
	i += fill2(err_buf, "miniRT: ", ctx);
	i += fill3(err_buf + i, ": ", strerror(errno), "\n");
	write(2, err_buf, i); */

int	err_per(int code, const char *ctx)
{
	(void) ctx;
	return (code);
}
