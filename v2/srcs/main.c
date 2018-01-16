/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:13:46 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/14 11:00:44 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_env_cnstr(t_env *env, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_memset(env, 0, sizeof(t_env));
	ft_camera_cnstr(&env->camera, ft_vec3(0, 0, 0), ft_vec3(0, 0, 1), 1.0f);
	env->mlx = mlx_init();
	env->win= mlx_new_window(env->mlx, WTH, HGT, "RTv1");
}

void		ft_compute(t_env *e)
{
	int		x;
	int		y;
	//double	u;
	//double	v;
	//t_vec3	point_screen;
	//t_vec3	ray_direction;
	t_ray	ray;
	t_sphere sphere;
	//t_plane	plane;
	//t_triangle triangle;

	//ft_triangle_cnstr(&triangle, ft_vec3(0, 3 , 5), ft_vec3(1, 1.2, 5), ft_vec3(1.9,1.2, 5));
	//ft_plane_cnstr(&plane, ft_vec3(0, 0, 10), ft_vec3(1, 1, 0));
	ft_sphere_cnstr(&sphere, ft_vec3(0, 0, 5), 1.0f);
	x = -1;
	while (++x < WTH && (y = -1))
	{
		while (++y < HGT)
		{
			/*u = (double) x / WTH;
			v = (double) y / HGT;
			point_screen = ft_vec3_add(ft_vec3_add(e->camera.p0, ft_vec3_times((
			ft_vec3_sub(e->camera.p1, e->camera.p0)), u)),
			ft_vec3_times((ft_vec3_sub(e->camera.p2, e->camera.p0)), v));
			ray_direction = ft_vec3_sub(point_screen, e->camera.cam_pos);
			ft_ray_cnstr(&ray,e->camera.cam_pos, ft_vec3_nor(ray_direction), 10000000.0f);*/
			double pixnormx = (x + 0.5) / WTH;
			double pixnormy = (y + 0.5) / HGT;
			double imageaspect = WTH / HGT;
			double pixremapx = (2 * pixnormx - 1) * imageaspect;
			double pixremapy = 1 - 2 * pixnormy;
			double pixcamerax = pixremapx * (atan(0.523599 / 2));
			double pixcameray = pixremapy * (atan(0.523599 / 2));
			t_vec3 camera = ft_vec3(pixcamerax, pixcameray, -1);
			t_vec3 ray_direction = ft_vec3_sub(camera, ft_vec3(0,0,0));
			ft_ray_cnstr(&ray, ft_vec3(0, 0, 0), ft_vec3_nor(ray_direction), 0);


			//if (ray_plane_intersect(&plane, &ray))
					//mlx_pixel_put(e->mlx, e->win, x, y, 0x0FF0000);
			//if (ray_triangle_intersect(&triangle, &ray))
			//		mlx_pixel_put(e->mlx, e->win, x, y, 0x00000FF);
			if (ray_sphere_intersect(&sphere, &ray))
					mlx_pixel_put(e->mlx, e->win, x, y, 0x000FF00);
		}
	}
}

int			main(int argc, char **argv)
{
	t_env e;

	ft_env_cnstr(&e, argc, argv);
	ft_compute(&e);
	mlx_hook(e.win, KEYRELEASE, KEYRELEASEMASK, ft_keyrelease, &e);
	mlx_hook(e.win, DESTROYNOTIFY, 0, ft_destroy, &e);
	mlx_loop(e.mlx);
	return (0);
}
