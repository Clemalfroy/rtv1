/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:13:46 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/12 19:14:21 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			sphere_intersect(t_sphere sphere, t_ray ray, double *t)
{
	t_vec3 o = ray.origin;
	t_vec3 d = ray.direction;
	t_vec3 oc = ft_vec3_sub(o, sphere.center);
	double b = 2 * ft_vec3_dot(oc, d);
	double c = ft_vec3_dot(oc, oc) - sphere.radius * sphere.radius;
	double disc = b * b - 4 * c;
	if (disc < 0)
		return (0);
	disc = sqrtf(disc);
	double t0 = -b - disc;
	double t1 = -b + disc;
	*t = (t0 < t1) ? t0 : t1;
	return (1);
}

int			plane_intersect(t_plane plane, t_ray ray, double *t)
{
	double dir_dot_norm = ft_vec3_dot(ray.direction, plane.normal);
	if (!dir_dot_norm)
		return (0);
	*t = ft_vec3_dot(ft_vec3_sub(plane.point, ray.origin), plane.normal);
	if (*t <= RAY_T_MIN || *t >= ray.tmax)
		return (0);
	return (1);
}

int			main(int argc, char **argv)
{
	int x;
	int y;
	t_ray ray;
	t_sphere sphere;
	t_env env;
	t_plane plane;

	env.mlx = mlx_init();
	env.win = mlx_new_window(env.mlx, WTH, HGT, "RTv1");
	sphere.center = ft_vec3(WTH / 2, HGT / 2, 50);
	sphere.radius = 80;
	plane.point = ft_vec3(WTH / 2, HGT / 2, 0);
	plane.normal = ft_vec3(1, 1, 1);
	(void)argv;
	(void)argc;
	y = -1;
	while (++y < HGT && (x = -1))
	{
		while (++x < WTH)
		{
			ray = ft_ray_cnstr(ft_vec3(x, y, 0), ft_vec3(0, 0, 1), RAY_T_MAX);

			double t = 200;

			if (sphere_intersect(sphere, ray, &t))
				mlx_pixel_put(env.mlx, env.win, x, y, 0x0AFF0000);
			if (plane_intersect(plane, ray, &t))
				mlx_pixel_put(env.mlx, env.win, x, y, 0x0A00FF00);
		}
	}
	mlx_loop(env.mlx);
	return (0);
}
