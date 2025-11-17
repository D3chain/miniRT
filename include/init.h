/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:35:18 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 11:49:51 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

int	init_app(struct s_app *app, int argc, char *argv[]);

int	init_scene(struct s_app *app, const char *filename);

#endif