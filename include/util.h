/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:20:05 by echatela          #+#    #+#             */
/*   Updated: 2025/12/17 10:32:16 by cgajean          ###   ########.fr       */
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
char	*next_tok(const char *str);

void	print_double3(t_double3 d, char *text);
void	print_color(t_color color, char *text);
void	print_color_linear(t_color_linear color, char *text);

void	randomize_material(t_material *original);


#endif
