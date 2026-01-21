/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:15:04 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 16:06:55 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H

# include "minirt_typedef.h"
# include "libft.h"

void	*xmalloc(t_app *app, size_t size);
void	*xcalloc(t_app *app, size_t size);
int		xopen(t_app *app, const char *file, int oflag);
char	*xstrdup(t_app *app, const char *source);

#endif
