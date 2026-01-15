/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_mouse.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 15:15:06 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/15 15:27:38 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_mouse_nobutton(struct s_mouse *mouse, int x, int y)
{
	struct s_mouse	m;

	m.button = mouse->button;
	m.pos_prv = mouse->pos_cur;
	m.pos_cur.x = x;
	m.pos_cur.y = y;
	m.dir.x = m.pos_cur.x - m.pos_prv.x;
	m.dir.y = m.pos_cur.y - m.pos_prv.y;
	*mouse = m;
}

void	update_mouse(struct s_mouse *mouse, int button, int x, int y)
{
	struct s_mouse	m;

	m.button = button;
	m.pos_prv = mouse->pos_cur;
	m.pos_cur.x = x;
	m.pos_cur.y = y;
	m.dir.x = m.pos_cur.x - m.pos_prv.x;
	m.dir.y = m.pos_cur.y - m.pos_prv.y;	
	*mouse = m;
}
