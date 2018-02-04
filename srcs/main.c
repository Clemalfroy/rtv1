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

static void		envctor(t_env *env, int argc, char **argv)
{
	(void)argc;
	(void)argv;
	ft_memset(env, 0, sizeof(t_env));
	env->mlx.mlx = mlx_init();
	env->mlx.win = mlx_new_window(env->mlx.mlx, WTH, HGT, "Rtv1");
	env->img.img = mlx_new_image(env->mlx.mlx, WTH, HGT);
	env->img.i_img = mlx_get_data_addr(env->img.img, &env->img.bpp,
		&env->img.size_l, &env->img.endian);
	env->fov = 60;
	env->shapes = shapector(env);
}

inline void		putpixel(t_env *env, int x, int y, int color)
{
	if (y >= HGT || x >= WTH || x < 0 || y < 0)
		return ;
	*(int *)&env->img.i_img[(y * env->img.size_l) +
		(x * (env->img.bpp / 8))] = color;
}

int			main(int argc, char **argv)
{
	t_env e;

	envctor(&e, argc, argv);
	compute(&e);
	mlx_put_image_to_window(e.mlx.mlx, e.mlx.win, e.img.img, 0, 0);
	mlx_hook(e.mlx.win, KEYRELEASE, KEYRELEASEMASK, e_keyrelease, &e);
	mlx_hook(e.mlx.win, DESTROYNOTIFY, 0, e_destroy, &e);
	mlx_expose_hook(e.mlx.win, e_expose, &e);
	mlx_loop_hook(e.mlx.mlx, e_loophook, &e);
	mlx_loop(e.mlx.mlx);
	return (0);
}