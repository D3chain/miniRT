/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 19:33:37 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/21 12:05:51 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_mouse_position_nobutton(t_mouse *mouse, int x, int y)
{
	t_mouse_pos	m;

	m.prv = mouse->pos.cur;
	m.cur.x = x;
	m.cur.y = y;
	m.dir.x = m.cur.x - m.prv.x;
	m.dir.y = m.cur.y - m.prv.y;
	mouse->pos = m;
}

void	update_mouse_position(t_mouse *mouse, int button, int x, int y)
{
	t_mouse_pos	m;

	m.prv = mouse->pos.cur;
	m.cur.x = x;
	m.cur.y = y;
	m.dir.x = m.cur.x - m.prv.x;
	m.dir.y = m.cur.y - m.prv.y;
	mouse->button = button;
	mouse->pos = m;
}
