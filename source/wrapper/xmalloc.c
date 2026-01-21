/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:11:02 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 11:45:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*xmalloc(t_app *app, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		app->status = ERR_SYS;
		err_per(app->status, "xmalloc");
		return (NULL);
	}
	return (ptr);
}
