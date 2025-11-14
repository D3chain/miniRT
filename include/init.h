/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 18:35:18 by echatela          #+#    #+#             */
/*   Updated: 2025/11/14 18:36:40 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

bool	init_data(struct s_data *data, int argc, char *argv[]);

bool	init_scene(struct s_data *data, const char *filename);

#endif