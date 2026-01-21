/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xstrdup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 16:07:39 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 11:45:24 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*xstrdup(t_app *app, const char *source)
{
	char	*ptr;

	ptr = ft_strdup(source);
	if (!ptr)
		app->status = ERR_SYS;
	return (ptr);
}
