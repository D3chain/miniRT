/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_mouse_motion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 14:07:09 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/14 15:26:42 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	mouse_left_button(struct s_app *app, t_int2 dir)
{
	if (dir.x > 0)
		;
	if (dir.x < 0)
		;
	if (dir.y > 0)
		;
	if (dir.y < 0)
		;
}

static void	mouse_right_button(struct s_app *app, t_int2 dir)
{
	if (dir.x > 0)
		;
	if (dir.x < 0)
		;
	if (dir.y > 0)
		;
	if (dir.y < 0)
		;
}

static void	mouse_middle_button(struct s_app *app, t_int2 dir)
{
	if (dir.x > 0)
		;
	if (dir.x < 0)
		;
	if (dir.y > 0)
		;
	if (dir.y < 0)
		;
}

int	event_mouse_motion(int x, int y, struct s_app *app)
{
	update_mouse_nobutton(&app->render.mouse, x, y);


	// if (m.button == Button1)
	// 	mouse_left_button(app, m.dir);
	// else if (m.button == Button3)
	// 	mouse_right_button(app, m.dir);
	// else if (m.button == Button2)
	// 	mouse_middle_button(app, m.dir);
	
	printf("(%d,%d)\n", app->render.mouse.pos_cur.x, app->render.mouse.pos_cur.y);

	return (0);
}

