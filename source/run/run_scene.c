/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:27:02 by echatela          #+#    #+#             */
/*   Updated: 2025/12/16 17:14:32 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define PHONG

void	init_ray(struct s_app *app, struct s_ray *ray, int x, int y)
{
	const t_double3	delta = plus3(mul3(app->scene.camera.viewport_u_px, (double)x), mul3(app->scene.camera.viewport_v_px, (double)y));
	const t_double3	px_pos = plus3(app->scene.camera.pixel00_loc, delta);

	ray->dir = minus3(px_pos, app->scene.camera.focal_center);
	ray->origin = app->scene.camera.focal_center;

}

t_double3 reflect(t_double3 incident, t_double3 normal)
{
	// Formule : R = I - 2(I·N)N
	const double	dot_product = dot(incident, normal);
	t_double3		scaled_normal = mul3(normal, 2.0 * dot_product);
	return (minus3(incident, scaled_normal));
}

double	fresnel_schlick(struct s_app *app, struct s_hit_info hit_info)
{
	const double	n1 = app->scene.environment_ior;
	const double	n2 = hit_info.material.ior;

	return (((n1 - n2) / (n1 + n2)) * ((n1 - n2) / (n1 + n2)));
}


/********************************************************************************************************************************************************* */

#ifdef PHONG
//	version speculaire "scientifisee" par IA pour obtenir les bons termes et une meilleure logique physique
//	voir historique des versions ci-dessous

//	MATERIAU PARSE

void trace(struct s_app *app, int x, int y)
{
	struct s_ray		primary_ray;
	struct s_ray		shadow_ray;
	struct s_hit_info	hit_info;
	struct s_hit_info	shadow_hit;
	
	// ============================================================================
	// PHASE 1 : INTERSECTION DU RAYON PRIMAIRE
	// ============================================================================
	// Lancer le rayon depuis la caméra à travers le pixel (x, y)
	
	init_ray(app, &primary_ray, x, y);
	hit_info = ray_hit(&primary_ray, app->scene.elems, app->scene.n_elem);
	
	// // Si aucune intersection, retourner couleur de fond
	// if (!hit_info.did_hit)
	// {
	// 	draw_pixel_to_img(&app->mlx.img, x, y, 0x000000);
	// 	return;
	// }
	
	// ============================================================================
	// PHASE 2 : GÉOMÉTRIE AU POINT D'IMPACT
	// ============================================================================
	// Vecteurs normalisés pour les calculs d'éclairage
	
	t_double3	P = hit_info.hit_point;                         			  	// Point d'impact
	t_double3	N = normalize3(hit_info.normal);                  				// Normale à la surface
	t_double3	V = normalize3(minus3(app->scene.camera.focal_center, P));  	// Direction vers caméra
	t_double3	L = normalize3(minus3(app->scene.light.coord, P)); 				// Direction vers lumière
	
	// ============================================================================
	// PHASE 3 : TEST D'OMBRE (SHADOW RAY)
	// ============================================================================
	// Lancer un rayon du point d'impact vers la lumière
	
	shadow_ray.origin = plus3(P, mul3(N, 1 + EPSILON));  						// Légèrement décalé pour éviter auto-intersection
	shadow_ray.dir = L;
	
	double	light_distance = norm3(minus3(app->scene.light.coord, P));
	shadow_hit = ray_hit(&shadow_ray, app->scene.elems, app->scene.n_elem);
	
	// Si un objet bloque entre le point et la lumière → ombre
	bool	in_shadow = (shadow_hit.did_hit && shadow_hit.dst < light_distance - EPSILON);
	
	// ============================================================================
	// PHASE 4 : CALCUL DE L'ÉCLAIRAGE (MODÈLE DE PHONG)
	// ============================================================================
	
	// --- 4.1 COMPOSANTE AMBIANTE (toujours présente) ---
	t_color	ambient = mul_color(
									hit_info.material.color,
									app->scene.ambient.color,
									app->scene.ambient.ratio
								);
	
	// --- 4.2 COMPOSANTE DIFFUSE (Lambert) ---
	t_color diffuse = {0};
	if (!in_shadow)
	{
		double	NdotL = fmax(0.0, dot(N, L));  					// Angle entre normale et lumière
		diffuse = mul_color(
								hit_info.material.color,
								app->scene.light.color,
								NdotL * app->scene.light.ratio
							);
	}
	
	// --- 4.3 COMPOSANTE SPÉCULAIRE (Phong) ---
	t_color specular = {0};
	if (!in_shadow)
	{
		t_double3		R = reflect(mul3(L, -1.0), N);     			// Direction de réflexion
		double			RdotV = fmax(0.0, dot(R, V));        		// Alignement réflexion-vue
		// double		shininess = 200.0;                      	// Netteté du reflet (10-200)
		// double		ks = 1.0;                              		// Intensité spéculaire (0-1)
		double			schlick = 0.95;								// Coefficient de Fresnel-Schlick (modulation de la reflexion speculaire)
		// double			schlick = fresnel_schlick(app, hit_info);
		// printf("schlick = %lf\n", schlick);
				
		double		specular_factor = pow(RdotV, hit_info.material.shininess);
		specular = scale_color(
									app->scene.light.color,
									specular_factor * hit_info.material.ks * schlick
								);
	}
	
	// ============================================================================
	// PHASE 5 : COMBINAISON FINALE
	// ============================================================================
	// Modèle de Phong : I = Ia + Id + Is
	t_color			final = color_add(ambient, color_add(diffuse, specular));

	// final = linear_to_srgb_approx(final);
	
	draw_pixel_to_img(&app->mlx.img, x, y, final.value);
}

// ============================================================================
// NOTES PHYSIQUES
// ============================================================================

// AMBIENT (Ia) :
//   - Approximation de la lumière indirecte globale
//   - Toujours présente, même dans l'ombre
//   - Évite les zones complètement noires

// DIFFUSE (Id) :
//   - Loi de Lambert : intensité ∝ cos(θ) où θ = angle entre N et L
//   - Représente la lumière absorbée puis réémise par le matériau
//   - Teintée par la couleur du matériau (kd)
//   - Absente si le point est dans l'ombre

// SPECULAR (Is) :
//   - Réflexion miroir imparfaite (selon la rugosité)
//   - Dépend de l'alignement entre R (réflexion) et V (vue)
//   - Teintée par la couleur de la lumière (pas du matériau pour diélectriques)
//   - Plus shininess est grand, plus le reflet est concentré
//   - Absente si le point est dans l'ombre

// OMBRES :
//   - Test binaire : objet entre point et lumière ?
//   - Supprime diffuse et specular (mais pas ambient)
//   - Shadow ray décalé de EPSILON pour éviter auto-intersection

// ============================================================================

#endif

/********************************************************************************************************************************************************* */

#ifdef NEW
//	version speculaire "scientifisee" par IA pour obtenir les bons termes et une meilleure logique physique
//	voir historique des versions ci-dessous

//	MATERIAU PARSE

void trace(struct s_app *app, int x, int y)
{
	struct s_ray		primary_ray;
	struct s_ray		shadow_ray;
	struct s_hit_info	hit_info;
	struct s_hit_info	shadow_hit;
	
	// ============================================================================
	// PHASE 1 : INTERSECTION DU RAYON PRIMAIRE
	// ============================================================================
	// Lancer le rayon depuis la caméra à travers le pixel (x, y)
	
	init_ray(app, &primary_ray, x, y);
	hit_info = ray_hit(&primary_ray, app->scene.elems, app->scene.n_elem);
	
	// // Si aucune intersection, retourner couleur de fond
	// if (!hit_info.did_hit)
	// {
	// 	draw_pixel_to_img(&app->mlx.img, x, y, 0x000000);
	// 	return;
	// }
	
	// ============================================================================
	// PHASE 2 : GÉOMÉTRIE AU POINT D'IMPACT
	// ============================================================================
	// Vecteurs normalisés pour les calculs d'éclairage
	
	t_double3	P = hit_info.hit_point;                         			  	// Point d'impact
	t_double3	N = normalize3(hit_info.normal);                  				// Normale à la surface
	t_double3	V = normalize3(minus3(app->scene.camera.focal_center, P));  	// Direction vers caméra
	t_double3	L = normalize3(minus3(app->scene.light.coord, P)); 				// Direction vers lumière
	
	// ============================================================================
	// PHASE 3 : TEST D'OMBRE (SHADOW RAY)
	// ============================================================================
	// Lancer un rayon du point d'impact vers la lumière
	
	shadow_ray.origin = plus3(P, mul3(N, 1 + EPSILON));  						// Légèrement décalé pour éviter auto-intersection
	shadow_ray.dir = L;
	
	double	light_distance = norm3(minus3(app->scene.light.coord, P));
	shadow_hit = ray_hit(&shadow_ray, app->scene.elems, app->scene.n_elem);
	
	// Si un objet bloque entre le point et la lumière → ombre
	bool	in_shadow = (shadow_hit.did_hit && shadow_hit.dst < light_distance - EPSILON);
	
	// ============================================================================
	// PHASE 4 : CALCUL DE L'ÉCLAIRAGE (MODÈLE DE PHONG)
	// ============================================================================
	
	// --- 4.1 COMPOSANTE AMBIANTE (toujours présente) ---
	t_color	ambient = mul_color(
									hit_info.material.color,
									app->scene.ambient.color,
									app->scene.ambient.ratio
								);
	
	// --- 4.2 COMPOSANTE DIFFUSE (Lambert) ---
	t_color diffuse = {0};
	if (!in_shadow)
	{
		double	NdotL = fmax(0.0, dot(N, L));  					// Angle entre normale et lumière
		diffuse = mul_color(
								hit_info.material.color,
								app->scene.light.color,
								NdotL * app->scene.light.ratio
							);
	}
	
	// --- 4.3 COMPOSANTE SPÉCULAIRE (Phong) ---
	t_color specular = {0};
	if (!in_shadow)
	{
		t_double3		R = reflect(mul3(L, -1.0), N);     			// Direction de réflexion
		double			RdotV = fmax(0.0, dot(R, V));        		// Alignement réflexion-vue
		// double		shininess = 200.0;                      	// Netteté du reflet (10-200)
		// double		ks = 1.0;                              		// Intensité spéculaire (0-1)
		double		schlick = 0.95;								// Coefficient de Fresnel-Schlick (modulation de la reflexion speculaire)
		// double			schlick = fresnel_schlick(app, hit_info);
		// printf("schlick = %lf\n", schlick);
				
		double		specular_factor = pow(RdotV, hit_info.material.shininess);
		specular = scale_color(
									app->scene.light.color,
									specular_factor * hit_info.material.ks * schlick
								);
	}
	
	// ============================================================================
	// PHASE 5 : COMBINAISON FINALE
	// ============================================================================
	// Modèle de Phong : I = Ia + Id + Is
	t_color			final = color_add(ambient, color_add(diffuse, specular));
	
	draw_pixel_to_img(&app->mlx.img, x, y, final.value);
}

// ============================================================================
// NOTES PHYSIQUES
// ============================================================================

// AMBIENT (Ia) :
//   - Approximation de la lumière indirecte globale
//   - Toujours présente, même dans l'ombre
//   - Évite les zones complètement noires

// DIFFUSE (Id) :
//   - Loi de Lambert : intensité ∝ cos(θ) où θ = angle entre N et L
//   - Représente la lumière absorbée puis réémise par le matériau
//   - Teintée par la couleur du matériau (kd)
//   - Absente si le point est dans l'ombre

// SPECULAR (Is) :
//   - Réflexion miroir imparfaite (selon la rugosité)
//   - Dépend de l'alignement entre R (réflexion) et V (vue)
//   - Teintée par la couleur de la lumière (pas du matériau pour diélectriques)
//   - Plus shininess est grand, plus le reflet est concentré
//   - Absente si le point est dans l'ombre

// OMBRES :
//   - Test binaire : objet entre point et lumière ?
//   - Supprime diffuse et specular (mais pas ambient)
//   - Shadow ray décalé de EPSILON pour éviter auto-intersection

// ============================================================================

#endif

/********************************************************************************************************************************************************* */

#ifdef OLD

//	version speculaire "scientifisee" par IA pour obtenir les bons termes et une meilleure logique physique
//	voir historique des versions ci-dessous

// MATERIAU HARDCODE

void trace(struct s_app *app, int x, int y)
{
	struct s_ray		primary_ray;
	struct s_ray		shadow_ray;
	struct s_hit_info	hit_info;
	struct s_hit_info	shadow_hit;
	
	// ============================================================================
	// PHASE 1 : INTERSECTION DU RAYON PRIMAIRE
	// ============================================================================
	// Lancer le rayon depuis la caméra à travers le pixel (x, y)
	
	init_ray(app, &primary_ray, x, y);
	hit_info = ray_hit(&primary_ray, app->scene.elems, app->scene.n_elem);
	
	// // Si aucune intersection, retourner couleur de fond
	// if (!hit_info.did_hit)
	// {
	// 	draw_pixel_to_img(&app->mlx.img, x, y, 0x000000);
	// 	return;
	// }
	
	// ============================================================================
	// PHASE 2 : GÉOMÉTRIE AU POINT D'IMPACT
	// ============================================================================
	// Vecteurs normalisés pour les calculs d'éclairage
	
	t_double3	P = hit_info.hit_point;                         			  	// Point d'impact
	t_double3	N = normalize3(hit_info.normal);                  				// Normale à la surface
	t_double3	V = normalize3(minus3(app->scene.camera.focal_center, P));  	// Direction vers caméra
	t_double3	L = normalize3(minus3(app->scene.light.coord, P)); 				// Direction vers lumière
	
	// ============================================================================
	// PHASE 3 : TEST D'OMBRE (SHADOW RAY)
	// ============================================================================
	// Lancer un rayon du point d'impact vers la lumière
	
	shadow_ray.origin = plus3(P, mul3(N, 1 + EPSILON));  						// Légèrement décalé pour éviter auto-intersection
	shadow_ray.dir = L;
	
	double	light_distance = norm3(minus3(app->scene.light.coord, P));
	shadow_hit = ray_hit(&shadow_ray, app->scene.elems, app->scene.n_elem);
	
	// Si un objet bloque entre le point et la lumière → ombre
	bool	in_shadow = (shadow_hit.did_hit && shadow_hit.dst < light_distance - EPSILON);
	
	// ============================================================================
	// PHASE 4 : CALCUL DE L'ÉCLAIRAGE (MODÈLE DE PHONG)
	// ============================================================================
	
	// --- 4.1 COMPOSANTE AMBIANTE (toujours présente) ---
	t_color	ambient = mul_color(
									hit_info.material.color,
									app->scene.ambient.color,
									app->scene.ambient.ratio
								);
	
	// --- 4.2 COMPOSANTE DIFFUSE (Lambert) ---
	t_color diffuse = {0};
	if (!in_shadow)
	{
		double	NdotL = fmax(0.0, dot(N, L));  					// Angle entre normale et lumière
		diffuse = mul_color(
								hit_info.material.color,
								app->scene.light.color,
								NdotL * app->scene.light.ratio
							);
	}
	
	// --- 4.3 COMPOSANTE SPÉCULAIRE (Phong) ---
	t_color specular = {0};
	if (!in_shadow)
	{
		t_double3	R = reflect(mul3(L, -1.0), N);     			// Direction de réflexion
		double		RdotV = fmax(0.0, dot(R, V));        		// Alignement réflexion-vue
		double		shininess = 200.0;                      	// Netteté du reflet (10-200)
		double		ks = 1.0;                              		// Intensité spéculaire (0-1)
		double		schlick = 0.95;								// Coefficient de Fresnel-Schlick (modulation de la reflexion speculaire)
				
		double		specular_factor = pow(RdotV, shininess);
		specular = scale_color(
									app->scene.light.color,
									specular_factor * ks * schlick
								);
	}
	
	// ============================================================================
	// PHASE 5 : COMBINAISON FINALE
	// ============================================================================
	// Modèle de Phong : I = Ia + Id + Is
	t_color			final = color_add(ambient, color_add(diffuse, specular));
	
	draw_pixel_to_img(&app->mlx.img, x, y, final.value);
}

// ============================================================================
// NOTES PHYSIQUES
// ============================================================================

// AMBIENT (Ia) :
//   - Approximation de la lumière indirecte globale
//   - Toujours présente, même dans l'ombre
//   - Évite les zones complètement noires

// DIFFUSE (Id) :
//   - Loi de Lambert : intensité ∝ cos(θ) où θ = angle entre N et L
//   - Représente la lumière absorbée puis réémise par le matériau
//   - Teintée par la couleur du matériau (kd)
//   - Absente si le point est dans l'ombre

// SPECULAR (Is) :
//   - Réflexion miroir imparfaite (selon la rugosité)
//   - Dépend de l'alignement entre R (réflexion) et V (vue)
//   - Teintée par la couleur de la lumière (pas du matériau pour diélectriques)
//   - Plus shininess est grand, plus le reflet est concentré
//   - Absente si le point est dans l'ombre

// OMBRES :
//   - Test binaire : objet entre point et lumière ?
//   - Supprime diffuse et specular (mais pas ambient)
//   - Shadow ray décalé de EPSILON pour éviter auto-intersection

// ============================================================================

#endif

/********************************************************************************************************************************************************* */


void	render(struct s_app *app)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WIN_WIDTH)
	{
		y = -1;
		while (++y < WIN_HEIGHT)
			trace(app, x, y);
	}
	mlx_put_image_to_window(app->mlx.mlx, app->mlx.win, app->mlx.img.img, 0, 0);
	printf("image printed\n");
}

int run_scene(struct s_app *app)
{
	app->mlx.win = mlx_new_window(app->mlx.mlx, app->mlx.width, app->mlx.height, "miniRT");
	render(app);
	mlx_hook(app->mlx.win, KeyPress, KeyPressMask, event_keyboard_press, app);
	mlx_loop(app->mlx.mlx);
	return (0);
}
