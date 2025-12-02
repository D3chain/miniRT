/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 12:52:39 by echatela          #+#    #+#             */
/*   Updated: 2025/12/02 15:54:54 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOAD_H
# define LOAD_H

# include "minirt.h"

int			load_scene(struct s_app *app, char *file);
t_double3	scan_double3(struct s_app *app, const char *tok);


#endif
