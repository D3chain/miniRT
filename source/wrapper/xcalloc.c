/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xcalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:19:57 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 14:55:35 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*xcalloc(t_app *app, size_t size)
{
	void	*ptr;

	ptr = xmalloc(app, size);
	if (ptr)
		ft_memset(ptr, 0, size);
	return (ptr);
}
