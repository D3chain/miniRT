/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomize_material.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:51:11 by cgajean           #+#    #+#             */
/*   Updated: 2025/12/15 13:34:25 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	RANDOMIZE material before we parse it correctly
*/

#include "minirt.h"

#include <time.h>

void	randomize_material(t_material *original)
{	
	original->ka = (double) rand() / RAND_MAX;
	original->kd = (double) rand() / RAND_MAX;
	original->ks = (double) rand() / RAND_MAX;
	
	original->ks_intensity = (double) rand() / RAND_MAX;
	original->shininess = rand() % 200;
	original->ior = (double) rand() / RAND_MAX;

	printf("ka = %lf\n", original->ka);
	printf("kd = %lf\n", original->kd);
	printf("ks = %lf\n", original->ks);
	printf("ksi = %lf\n", original->ks_intensity);
	printf("shi = %lf\n", original->shininess);
	printf("ior = %lf\n\n", original->ior);
}

