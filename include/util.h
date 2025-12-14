/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:20:05 by echatela          #+#    #+#             */
/*   Updated: 2025/12/14 16:38:03 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "minirt.h"

int		scan_int(struct s_app *app, int *res, const char *str);
int		scan_uint8_t(struct s_app *app, uint8_t *res, const char *str);
int		scan_double(struct s_app *app, double *res, const char *str);
int		scan_double3(struct s_app *app, t_double3 *res, const char *str);
int		scan_color(struct s_app *app, t_color *res, const char *str);
int		scan_elem(struct s_app *app, const char *line);
char	*next_tok(const char *str);

void	print_double3(t_double3 d, char *text);

// t_color	color_blend(t_color object, t_color light);


#endif
