/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xmalloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:11:02 by echatela          #+#    #+#             */
/*   Updated: 2025/11/16 17:30:31 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	*xmalloc(struct s_data *data, size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		data->status = errno;
		err_per(errno, "xmalloc");
		return (NULL);
	}
	return (ptr);
}
