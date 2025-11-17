/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:57:28 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 16:19:57 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_H
# define RUN_H

# include "minirt.h"

int run_scene(struct s_app *app);

int	event_keyboard_press(int key, struct s_app *app);

#endif