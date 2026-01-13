/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:15:04 by echatela          #+#    #+#             */
/*   Updated: 2026/01/13 17:14:49 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H

# include "minirt.h"

void	*xmalloc(struct s_app *app, size_t size);
void	*xcalloc(struct s_app *app, size_t size);
int		xopen(struct s_app *app, const char *file, int oflag);

#endif
