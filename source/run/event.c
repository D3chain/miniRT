/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: echatela <echatela@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:20:04 by echatela          #+#    #+#             */
/*   Updated: 2025/11/17 16:26:25 by echatela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	event_keyboard_press(int key, struct s_app *app)
{
	if (key == XK_Escape)
		mlx_loop_end(app->mlx.mlx);
	return (0);
}
