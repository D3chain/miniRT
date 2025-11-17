/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:15:04 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 11:50:19 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WRAPPER_H
# define WRAPPER_H

# include "minirt.h"

void	*xmalloc(struct s_app *app, size_t size);
int		xopen(struct s_app *app, const char *file, int oflag);


#endif