/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:20:05 by echatela          #+#    #+#             */
/*   Updated: 2026/01/21 12:15:14 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "minirt.h"

# ifdef USE_DBL_NUMBER
#  define FLT_FMT	"%.2lf"
# else
#  define FLT_FMT	"%.2f"
# endif
 
# define REAL		FLT_FMT
# define REAL3		REAL","REAL","REAL
# define INT			"%d"
# define	COLOR_RGB	INT","INT","INT

int		scan_int(t_app *app, int *res, const char *str);
int		scan_uint8_t(t_app *app, uint8_t *res, const char *str);
int		scan_t_real(t_app *app, t_real *res, const char *str);
int		scan_t_real3(t_app *app, t_real3 *res, const char *str);
int		scan_color(t_app *app, t_color *res, const char *str);

void	print_real3(t_real3 d, char *text);
void	print_color(t_color color, char *text);
void	print_color_lin(t_color_lin color, char *text);

void	print_bvh_tree(t_bvh_base *root);
void	print_render(t_app *app);
void	print_camera(t_app *app);

void	print_map(t_app *app);
void	print_rcal(t_app *app, int fd);
void	print_shapes(int fd, t_bvh_elem_box *e);
void	print_shape_material(int fd, t_material *m);

#endif
