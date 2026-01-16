/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mouse_position.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:15:06 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/16 15:24:31 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_mouse_position_nobutton(struct s_mouse *mouse, int x, int y)
{
	struct s_mouse_position	m;;

	m.prv = mouse->pos.cur;
	m.cur.x = x;
	m.cur.y = y;
	m.dir.x = m.cur.x - m.prv.x;
	m.dir.y = m.cur.y - m.prv.y;
	mouse->pos = m;
}

void	update_mouse_position(struct s_mouse *mouse, int button, int x, int y)
{
	struct s_mouse_position	m;

	m.prv = mouse->pos.cur;
	m.cur.x = x;
	m.cur.y = y;
	m.dir.x = m.cur.x - m.prv.x;
	m.dir.y = m.cur.y - m.prv.y;	
	mouse->button = button;
	mouse->pos = m;
}
