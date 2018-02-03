/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmalfroy <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 15:13:46 by cmalfroy          #+#    #+#             */
/*   Updated: 2017/12/17 16:36:52 by cmalfroy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_env_cnstr(t_env *env, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_memset(env, 0, sizeof(t_env));
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WTH, HGT, "RTv1");
	env->img = mlx_new_image(env->mlx, WTH, HGT);
	env->i_img = mlx_get_data_addr(env->img, &env->bpp, &env->size_l, &env->endian);
}

void		ft_put_pixel(t_env *env, int x, int y, int color)
{
	if (y >= HGT || x >= WTH || x < 0 || y < 0)
		return ;
	*(int *)&env->i_img[(y * env->size_l) + (x * (env->bpp / 8))] = color;
}

void		fill_shape(t_shape list[7])
{
	t_sphere shapelist[5];
	t_plane	plane;

	ft_plane_cnstr(&plane, ft_vec3(0, -4, 0), ft_vec3(0,1,0));
	ft_sphere_cnstr(&shapelist[0], ft_vec3(0,1,-20), 5);
	ft_sphere_cnstr(&shapelist[1], ft_vec3(8,-1,-15), 3);
	ft_sphere_cnstr(&shapelist[2], ft_vec3(8,0,-22), 4);
	ft_sphere_cnstr(&shapelist[3], ft_vec3(-8.5,0,-15), 4);
	ft_sphere_cnstr(&shapelist[4], ft_vec3(-6,5,-28), 7);
	shape_assoc_sphere(&list[0], shapelist[0], ft_vec3(1.0, 0.32, 0.36));
	shape_assoc_sphere(&list[1], shapelist[1], ft_vec3(0.98, 0.76, 0.46));
	shape_assoc_sphere(&list[2], shapelist[2], ft_vec3(0.65, 0.77, 0.97));
	shape_assoc_sphere(&list[3], shapelist[3], ft_vec3(0.8, 0.8, 0.8));
	shape_assoc_sphere(&list[4], shapelist[4], ft_vec3(0.28, 0.64, 0.34));
	shape_assoc_plane(&list[5], plane, ft_vec3(0.2, 0.2, 0.2));
}

void		ft_compute(t_env *e)
{
	int		x;
	int		y;
	int		i;
	int		j;
	t_shape list[7];

	fill_shape(list);
	x = -1;
	while (++x < WTH && (y = -1))
	{
		while (++y < HGT && (i = -1))
		{
			double pixnormx = (x + 0.5) / WTH;
			double pixnormy = (y + 0.5) / HGT;
			double pixremapx = (2 * pixnormx - 1) * WTH / HGT;
			double pixremapy = 1 - 2 * pixnormy;
			double pixcamerax = pixremapx * (tan((2) / 2));
			double pixcameray = pixremapy * (tan((2)/ 2));
			t_vec3 camera = ft_vec3(pixcamerax, pixcameray, -1);
			t_vec3 ray_origin = ft_vec3(0, 0, 0);
			t_vec3 ray_direction = ft_vec3_normalize(ft_vec3_sub(camera, ray_origin));
			double mint = INFINITY;
			int		shapehit = -1;
			double	t0 = 0.0f;
			while (++i < 6 && (j = -1))
			{
				int hit = ray_shape_intersect(&list[i], ray_origin, ray_direction, &t0);
				if (hit && t0 < mint && (shapehit = i) >= 0)
				{
					mint = t0;
					t_vec3 p0 = ft_vec3_add(ray_origin, (ft_vec3_times(ray_direction, mint)));
					t_vec3 lighposition = ft_vec3(0, 20, 0);
					t_vec3 lightintensity = ft_vec3(1, 1, 1);
					t_vec3 diffusecolor = list[shapehit].color;
					t_vec3 specularcolor = ft_vec3(0.1,0.1,0.1);
					int shininess = 0;
					t_vec3 normal = ft_vec3_normalize(shape_calculate_normal(&list[shapehit], p0, &specularcolor, &shininess));
					t_vec3 ambiant = ft_vec3_mul(list[shapehit].color, ft_vec3(0.1, 0.1, 0.1));
					t_vec3 lightray = ft_vec3_normalize(ft_vec3_sub(lighposition, p0));
					t_vec3 diffuse = ft_vec3_times(ft_vec3_mul(diffusecolor, lightintensity), ft_max(0.0f, ft_vec3_dot(lightray, normal)));
					t_vec3 reflection = ft_vec3_normalize(ft_vec3_sub(ft_vec3_times(ft_vec3_times(normal, ft_vec3_dot(lightray, normal)), 2), lightray));
					double maxcalc = ft_max(0.0f, ft_vec3_dot(reflection, ft_vec3_normalize(ft_vec3_sub(ray_origin, p0))));
					t_vec3 specular = ft_vec3_mul(ft_vec3_times(lightintensity, pow(maxcalc, shininess)), specularcolor);
					int lightshapehit = -1;
					while (++j < 6)
					{
						int lighthit = ray_shape_intersect(&list[j], ft_vec3_add(p0, (ft_vec3_times(normal, 1e-4f))), lightray, &t0);
						if (lighthit && t0 < mint && (lightshapehit = j) >= 0)
							mint = t0;
					}
					if (lightshapehit != -1)
						ft_put_pixel(e, x, y, ft_color(ft_vec3_mul(list[lightshapehit].color, ambiant)));
					else
						ft_put_pixel(e, x, y, ft_color(ft_vec3_add(specular, diffuse)));
				}
				if (shapehit == -1)
					ft_put_pixel(e, x, y, 0);
			}
		}
	}
}

int			main(int argc, char **argv)
{
	t_env e;

	ft_env_cnstr(&e, argc, argv);
	ft_compute(&e);
	mlx_put_image_to_window(e.mlx, e.win, e.img, 0, 0);
	mlx_hook(e.win, KEYRELEASE, KEYRELEASEMASK, ft_keyrelease, &e);
	mlx_hook(e.win, DESTROYNOTIFY, 0, ft_destroy, &e);
	mlx_loop(e.mlx);
	return (0);
}
