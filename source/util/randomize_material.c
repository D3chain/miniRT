/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomize_material.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:51:11 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/13 23:42:12 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	RANDOMIZE material before we parse it correctly
*/

#include "minirt.h"

#include <time.h>

void	randomize_material(t_material *original)
{	
	original->ka = 0.1;
	original->kd = 0.7;
	original->ks = 0.2;
		
	original->shininess = 400;
	original->ior = 1.5;

	original->kr = 0.7;
	original->kt = 0.7;
}
