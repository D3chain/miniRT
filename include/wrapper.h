/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:15:04 by echatela          #+#    #+#             */
/*   Updated: 2025/12/15 15:12:41 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H

# include "minirt.h"

void	*xmalloc(struct s_app *app, size_t size);
int		xopen(struct s_app *app, const char *file, int oflag);

#endif