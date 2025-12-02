/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:11:02 by echatela          #+#    #+#             */
/*   Updated: 2025/12/02 11:49:32 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*xmalloc(struct s_app *app, size_t size)
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
