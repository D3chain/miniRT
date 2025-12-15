/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomize_material.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:51:11 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/15 15:43:56 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	RANDOMIZE material before we parse it correctly
*/

#include "minirt.h"

#include <time.h>

void	randomize_material(t_material *original)
{	
	original->ks = (double) rand() / RAND_MAX;	
	original->shininess = rand() % 200;
}

