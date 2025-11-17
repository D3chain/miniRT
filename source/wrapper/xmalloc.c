/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:11:02 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 11:51:05 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*xmalloc(struct s_app *app, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		app->status = errno;
		err_per(errno, "xmalloc");
		return (NULL);
	}
	return (ptr);
}
