/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:35:18 by echatela          #+#    #+#             */
/*   Updated: 2025/11/16 17:33:15 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

bool	init_data(struct s_data *data, int argc, char *argv[]);

bool	init_scene(struct s_data *data, const char *filename);

#endif