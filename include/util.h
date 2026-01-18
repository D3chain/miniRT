/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:20:05 by echatela          #+#    #+#             */
/*   Updated: 2026/01/18 13:46:56 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTIL_H
# define UTIL_H

# include "minirt.h"

int		scan_int(struct s_app *app, int *res, const char *str);
int		scan_uint8_t(struct s_app *app, uint8_t *res, const char *str);
int		scan_t_real(struct s_app *app, t_real *res, const char *str);
int		scan_t_real3(struct s_app *app, t_real3 *res, const char *str);
int		scan_color(struct s_app *app, t_color *res, const char *str);
char	*next_tok(const char *str);

void	print_real3(t_real3 d, char *text);
void	print_color(t_color color, char *text);
void	print_color_linear(t_color_linear color, char *text);

void	print_bvh_tree(t_bvh_base *root);
void	print_render(struct s_app *app);
void	print_camera(struct s_app *app);

#endif
