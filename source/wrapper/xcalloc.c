/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 14:03:14 by fox               #+#    #+#             */
/*   Updated: 2026/01/09 14:05:06 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*xcalloc(struct s_app *app, size_t size)
{
	void	*ptr;

	ptr = xmalloc(app, size);
	if (!app->status)
		ft_memset(ptr, 0, size);
	return (ptr);
}
