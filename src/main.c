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

int	rtv1(t_env *e)
{
	compute(e);
	mlx_put_image_to_window(e->mlx.mlx, e->mlx.win, e->img.img, 0, 0);
	mlx_hook(e->mlx.win, KEYRELEASE, KEYRELEASEMASK, e_keyrelease, e);
	mlx_hook(e->mlx.win, DESTROYNOTIFY, 0, e_destroy, e);
	mlx_expose_hook(e->mlx.win, e_expose, e);
	mlx_loop_hook(e->mlx.mlx, e_loophook, e);
	mlx_loop(e->mlx.mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_env	*env;

	if (argc != 2)
		return (1);
	if ((fd = open(argv[1], O_RDONLY)) < 0)
	{
		ft_putf(STDERR_FILENO, "%s: %e\n", argv[1], errno);
		return (1);
	}
	ft_memset(env = alloca(sizeof(t_env)), 0, sizeof(t_env));
	env->mlx.mlx = mlx_init();
	env->mlx.win = mlx_new_window(env->mlx.mlx, WTH, HGT, "Rtv1");
	env->img.img = mlx_new_image(env->mlx.mlx, WTH, HGT);
	env->img.addr = mlx_get_data_addr(env->img.img, &env->img.bpp,
		&env->img.size_l, &env->img.endian);
	env->fov = 60;
	return (shapeparse(env, fd, rtv1));
}