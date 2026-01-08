/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   randomize_material.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 12:51:11 by cgajean           #+#    #+#             */
/*   Updated: 2026/01/08 11:34:36 by cgajean          ###   ########.fr       */
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
		
	original->ks_intensity = 1.0;
	original->shininess = 400;
	original->ior = 1.5;

	original->kr = 0.7;
	original->kt = 0.7;
}


// void	randomize_material(t_material *original)
// {	
// 	double	tmp_a;
// 	double	tmp_d;
// 	double	tmp_s;
// 	double	tmp_ads;
	
// 	tmp_a = (double) rand() / RAND_MAX;
// 	tmp_d = (double) rand() / RAND_MAX;
// 	tmp_s = (double) rand() / RAND_MAX;	

// 	tmp_a = tmp_a < 0.1 ? 0.1 : tmp_a;
// 	tmp_d = tmp_d < 0.4 ? 0.5 255: tmp_d;
// 	tmp_s = tmp_s < 0.6 ? 0.8 : tmp_s;
	
// 	tmp_a = tmp_a > 0.2 ? 0.2 : tmp_a;
// 	tmp_d = tmp_d > 0.6 ? 0.6 : tmp_d;
// 	tmp_s = tmp_s > 0.8 ? 0.8 : tmp_s;
	
// 	tmp_ads = tmp_a + tmp_d + tmp_s;
	
// 	original->ka = tmp_a / tmp_ads;
// 	original->kd = tmp_d / tmp_ads;;
// 	original->ks = tmp_s / tmp_ads;;
	
// 	original->ks_intensity = (double) rand() / RAND_MAX;
// 	original->shininess = rand() % 200;
// 	original->ior = 1.5;

// 	printf("ka = %lf\n", original->ka);
// 	printf("kd = %lf\n", original->kd);
// 	printf("ks = %lf\n", original->ks);
// 	printf("ksi = %lf\n", original->ks_intensity);
// 	printf("shi = %lf\n", original->shininess);
// 	printf("ior = %lf\n\n", original->ior);
// }


// Matériaux mats (plâtre, bois non verni)
// ka = 0.1 - 0.2
// kd = 0.6 - 0.8
// ks = 0.0 - 0.1
// shininess = 5 - 20

// Plastique
// ka = 0.1 - 0.2
// kd = 0.4 - 0.6
// ks = 0.2 - 0.4
// shininess = 30 - 100

// Métal (or, cuivre)
// ka = 0.1 - 0.2
// kd = 0.1 - 0.3
// ks = 0.5 - 0.8
// shininess = 100 - 300

// Miroir/Chrome
// ka = 0.05 - 0.1
// kd = 0.0 - 0.1
// ks = 0.8 - 0.9
// shininess = 200 - 400

// Verre (avec transmission)
// ka = 0.0 - 0.05
// kd = 0.0 - 0.1
// ks = 0.1 - 0.2
// kt = 0.7 - 0.9
// ior = 1.5 - 1.9

// Plastique   : ior = 1.45 - 1.55
// Bois vernis : ior = 1.5
// Verre       : ior = 1.5 - 1.9
// Eau         : ior = 1.33
// Diamant     : ior = 2.42
// Pierre      : ior = 1.5 - 1.6